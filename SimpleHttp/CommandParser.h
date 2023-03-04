#pragma once
// #pragma once COMMAND_PARSER
// COMMAND PARSER TO BE INCLUDED IN VERSION 2
#include <string>
#include <iostream>
#include <stdlib.h>


class Commands {
private:
    std::string command;
    int CMDMODE;
    // std::string help="help";
    // std::string quit="quit";
    // std::string restart="restart";
    // std::string exit="exit";


public:
    Commands(int CMDMODE) {
        // Default comnstructor
        this->CMDMODE = CMDMODE;
    }

    void PrintHelp() {
        std::cout << "restart : Restart Server" << std::endl;
        std::cout << "help : Restart Server" << std::endl;
        std::cout << "exit/quit : Restart Server" << std::endl;
    }

    void Exit_Function() {
        std::cout << "Do you really want to exit ? (y/n) ";
        char answer;
        std::cin >> answer;
        if (answer == 'y')
            exit(0);
        else
            return;
    }

    void ParseCommands() {
        std::cout << "server >> ";
        std::cin >> this->command;
        if (command == "help")
            PrintHelp();
        if (command == "quit")
            Exit_Function();
        if (command == "exit")
            Exit_Function();

    }
};