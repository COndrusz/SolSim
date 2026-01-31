#pragma once
#include <stdio.h>
#include <mutex>
#include <errno.h>
#include <chrono>

enum LogPriority
{
	TRACE, DEBUG, INFO, WARN, ERROR, FATAL
};


class Logger
{
private:
	static LogPriority Priority;
	static std::mutex Log_Mutex;
	static FILE* file;
	static const char* filepath;
	static errno_t err;
public:
	static void Set_Priority(LogPriority New_Priority)
	{
		Priority = New_Priority;
	};

	static void WriteToFile()
	{
		filepath = "log.txt";
		Enable_File_Output(filepath);
	};

	static void WriteToFile(const char* filepath)
	{
		Enable_File_Output(filepath);
	}

	static void CloseFileOutput()
	{
		Free_File();
	}

	template<typename... Args>
	static void trace(const char* message, Args... args)
	{log("TRACE\t", TRACE, message, args...);}

	template<typename... Args>
	static void debug(const char* message, Args... args)
	{log("DEBUG\t", DEBUG, message, args...);}

	template<typename... Args>
	static void info(const char* message, Args... args)
	{log("INFO\t", INFO, message, args...);}

	template<typename... Args>
	static void warn(const char* message, Args... args)
	{log("WARN\t", WARN, message, args...);}

	template<typename... Args>
	static void error(const char* message, Args... args)
	{log("ERROR\t", ERROR, message, args...);}

	template<typename... Args>
	static void fatal(const char* message, Args... args)
	{log("FATAL\t", FATAL, message, args...);}


private:
	template<typename... Args>
	static void log(const char* priority_str, LogPriority priority, const char* message, Args... args)
	{
		if (Priority <= priority)
		{
			auto now_sy = std::chrono::system_clock::now();
			time_t tt = std::chrono::system_clock::to_time_t(now_sy);

			// Ensure that other threads wait until we leave current scope
			std::scoped_lock lock(Log_Mutex);
			// Used to add timestamps to log

			char str[26];
			ctime_s(str, sizeof(str), &tt);
			// remove the newline character at the end of the string
			str[strlen(str) - 1] = ' ';
			printf(str);

			printf(priority_str);
			printf(message, args...);
			printf("\n");
			// End of scope

			if (file)
			{
				fprintf(file, str);
				fprintf(file, priority_str);
				fprintf(file, message, args...);
				fprintf(file, "\n");
			}
		}
	}

	static void Enable_File_Output(const char* filepath)
	{
		if (file != 0)
		{
			fclose(file);
		}
		err = fopen_s(&file, filepath, "a");
		if (file == 0)
		{
			printf("Failed to open file at %s", filepath);
		}
	}

	static void Free_File() 
	{
		fclose(file);
		file = 0;
	}
};

