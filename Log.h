#pragma once
#include <string>
#include <iostream>
#include <windows.h>


#define GET_FUNCTION_NAME __FUNCSIG__
#define PRINT_FUNCTION_NAME(log_level) Log::LogMessage(GET_FUNCTION_NAME, log_level);
#define DETAIL_LOG(message, log_level) Log::LogMessage(std::string("In function: ") + GET_FUNCTION_NAME, log_level); Log::LogMessage(message, log_level);

enum class LogLevel {
	Info,
	Warning,
	Error
};

class Log{
public:
	Log();
	
	// template function must be written inline or in the header file
	template<typename T>
	static void LogMessage(T&& message, LogLevel level = LogLevel::Info)
	{
		int log_color = WHITE;
		switch (level)
		{
		case LogLevel::Warning:
			log_color = YELLOW;
			break;
		case LogLevel::Error:
			log_color = RED;
			break;
		default:	// other cases is already considered in the initialization of "color = WHITE"
			break;
		}

		HANDLE std_handle = GetStdHandle(STD_OUTPUT_HANDLE);

		// change color of output text
		SetConsoleTextAttribute(std_handle, log_color);

		std::cout << message << std::endl;

		// set it to the initial state
		SetConsoleTextAttribute(std_handle, WHITE);
	}

private:

	//Color for output logs
	static const int WHITE = 15;
	static const int YELLOW = 6;
	static const int RED = 4;	
};

