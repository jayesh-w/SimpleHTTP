#pragma once
// Socket Class 
// Functionality :
// Open a socket connect, 
// Bind the socket
// Listen to incoming connection 
// closes the Connection
// Factory function should return the socket handler for sending html responses

#include <winsock2.h>
#include <string>
#include "Response.h"
#include "RequestParser.h"
#include "Logger.h"


namespace server {
    class Socket {
    private:
        WSADATA wsa_data;
        SOCKADDR_IN server_addr, client_addr;
        int VERSION;
        int CONNECTION_TYPE;
        int PROTOCOL;
        int PORT;
        int client_addr_size;
        std::string IP_ADDRESS;
        SOCKET server;
        SOCKET client;
        RequestParser* m_pRequestParser;
        Response* m_pResponse;
        Logger log;


    public:
        Socket(int ver, int conn_type, int protocol, std::string ip, int port);
        int createSocket();
        void bindSocket();
        void listenConnection();
        int acceptClientConnection();
        int Request();
        int SendResponse();
        void closeClient();
        ~Socket();

    };


    Socket* CreateServer(int VERSION = AF_INET, int CONNECTION_TYPE = SOCK_STREAM, int PROTOCOL = 0, std::string IP = "127.0.0.1", int PORT = 8080);


}