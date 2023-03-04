// SimpleHttp.cpp : This file contains the 'main' function. Program execution begins and ends there.


#include <iostream>
#include "Socket.h"
#include "Logger.h"
int main() {
    // Initialize the socket connection...
    std::cout << "*************** Welcome to Simple Server *******************" << std::endl;
    server::Socket* server = server::CreateServer();
    while (true) {
        if (server->acceptClientConnection() != INVALID_SOCKET) {
            int recv_bytes = server->Request();
            if (recv_bytes > 0) {
                int sendInt = server->SendResponse();
                if (sendInt == SOCKET_ERROR) {
                    server->closeClient();
                    return 1;
                }
                else {
                    server->closeClient();
                }
                
            }
        }
        
    }
    return 0;
}


