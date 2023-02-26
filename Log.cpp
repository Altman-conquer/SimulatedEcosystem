#include "Log.h"
#include <iostream>
#include <windows.h>

void Log::LogMessage(const std::string& message, LogLevel level)
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
	// other cases is already considered in the initialization of "color = WHITE"
	}

	HANDLE std_handle = GetStdHandle(STD_OUTPUT_HANDLE);
	
	// change color of output text
	SetConsoleTextAttribute(std_handle, log_color);
	
	std::cout << message << std::endl;
	
	// set it to the initial state
	SetConsoleTextAttribute(std_handle, WHITE);
}
