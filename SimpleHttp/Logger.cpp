#include "Logger.h"
#include <string>
#include <time.h>
#include <iostream>

Logger::Logger() {
    msg("Starting the Logger Now...");
}

std::string Logger::currentDateTime() {
    time_t     now = time(0);
    struct tm  tstruct;
    char       buf[80];
    int err = localtime_s(&tstruct, &now);
    strftime(buf, sizeof(buf), "[%Y-%m-%d::%X]", &tstruct);

    return buf;
}

void Logger::msg(std::string message) {
    std::cout << currentDateTime() << message << std::endl;
}

void Logger::Errmsg(std::string message) {
    std::cout << currentDateTime() <<" ERROR! " << message << std::endl;
}