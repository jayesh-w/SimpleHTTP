#pragma once 
#include <string>
class Logger {
public:
	Logger();
	std::string currentDateTime();
	void msg(std::string message);
	void Errmsg(std::string message);
};