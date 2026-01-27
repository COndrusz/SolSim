#pragma once
#include <stdio.h>
#include <mutex>

enum LogPriority
{
	TRACE, DEBUG, INFO, WARN, ERROR, FATAL
};


class Logger
{
private:
	static LogPriority Priority;
	static std::mutex Log_Mutex;

public:
	static void Set_Priority(LogPriority New_Priority)
	{
		Priority = New_Priority;
	};

	template<typename... Args>
	static void trace(const char* message, Args... args)
	{
		if (Priority <= TRACE)
		{
			// Ensure that other threads wait until we leave current scope
			std::scoped_lock lock(Log_Mutex);
			printf("[Trace]\t");
			printf(message, args...);
			printf("\n");
			// End of scope
		}
	}

	template<typename... Args>
	static void debug(const char* message, Args... args)
	{
		if (Priority <= DEBUG)
		{
			std::scoped_lock lock(Log_Mutex);
			printf("[Debug]\t");
			printf(message, args...);
			printf("\n");
		}
	}

	template<typename... Args>
	static void info(const char* message, Args... args)
	{
		if (Priority <= INFO)
		{
			std::scoped_lock lock(Log_Mutex);
			printf("[Info]\t");
			printf(message, args...);
			printf("\n");
		}
	}

	template<typename... Args>
	static void warn(const char* message, Args... args)
	{
		if (Priority <= WARN)
		{
			std::scoped_lock lock(Log_Mutex);
			printf("[Warn]\t");
			printf(message, args...);
			printf("\n");
		}
	}

	template<typename... Args>
	static void error(const char* message, Args... args)
	{
		if (Priority <= ERROR)
		{
			std::scoped_lock lock(Log_Mutex);
			printf("[Error]\t");
			printf(message, args...);
			printf("\n");
		}
	}

	template<typename... Args>
	static void fatal(const char* message, Args... args)
	{
		if (Priority <= FATAL)
		{
			std::scoped_lock lock(Log_Mutex);
			printf("[Fatal]\t");
			printf(message, args...);
			printf("\n");
		}
	}

};

