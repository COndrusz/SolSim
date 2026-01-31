#include "Logger.h"

LogPriority Logger::Priority = INFO;
std::mutex Logger::Log_Mutex;
FILE* Logger::file = 0;
const char* Logger::filepath = 0;
errno_t Logger::err = 0;