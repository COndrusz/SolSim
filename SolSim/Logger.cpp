#include "Logger.h"

LogPriority Logger::Priority = INFO;
std::mutex Logger::Log_Mutex;