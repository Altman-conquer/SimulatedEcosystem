#pragma once
#include <string>

enum class LogLevel {
	Info,
	Warning,
	Error
};

class Log{
public:
	Log();
	
	static void LogMessage(const std::string message, LogLevel level = LogLevel::Info);

private:

	//Color for output logs
	static const int WHITE = 15;
	static const int YELLOW = 6;
	static const int RED = 4;	
};

