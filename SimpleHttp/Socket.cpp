#include "Socket.h"
#include <winsock2.h>
#include <sstream>
#include <iostream>
#include <string>
#pragma warning(disable : 4996)
#include "RequestParser.h"
#include <stdlib.h>
#include "Response.h"
#include "Logger.h"


using namespace server;

void log(std::string content) {
    std::cout << content << std::endl;
}

Socket::Socket(int ver, int conn_type, int protocol, std::string ip, int port) {
    if (::WSAStartup(MAKEWORD(2, 2), &wsa_data) != 0) {
        ::log("WSA startup failed...");
    }
    else {
        this->VERSION = ver;
        this->CONNECTION_TYPE = conn_type;
        this->PROTOCOL = protocol;
        this->IP_ADDRESS = ip;
        this->PORT = port;
        this->server_addr.sin_addr.s_addr = inet_addr(ip.c_str());;
        this->server_addr.sin_family = ver;
        this->server_addr.sin_port = htons(port);
        this->client_addr_size = sizeof(client_addr);
        this->log = Logger();
    }
}

int Socket::createSocket() {
    this->server = ::socket(this->VERSION, this->CONNECTION_TYPE, this->PROTOCOL);
    if (this->server < 0) {
        log.msg("Socket Creation Failed");
        exit(1);
    }
    log.msg("Socket Created Successfully");
    return this->server;
}

void Socket::bindSocket() {
    int bindCode = bind(this->server, (SOCKADDR*)&(this->server_addr), sizeof(this->server_addr));
    if (bindCode < 0) {
        log.msg("Socket Binding failed");
        exit(1);
    }
    log.msg("Socket Binded Successfully");

}

void Socket::listenConnection() {
    int listenCode = listen(this->server, 0);
    if (listenCode < 0) {
        log.msg("Error is listening server.... Exiting");
        exit(1);
    }
    std::ostringstream ss;
    ss << "\n*** Listening on ADDRESS: " << inet_ntoa(this->server_addr.sin_addr) << " PORT: " << ntohs(this->server_addr.sin_port) << " ***\n\n";
    log.msg(ss.str());

}

Socket::~Socket() {
    closesocket(this->server);
    WSACleanup();
    log.msg("Closing the Server Now.....");
    exit(0);
}

int Socket::acceptClientConnection() {
    this->client = accept(this->server, reinterpret_cast<SOCKADDR*>(&client_addr), &client_addr_size);
    if (this->client != INVALID_SOCKET)
        return this->client;
    else {
        log.msg("Client Connection Error...");
        return INVALID_SOCKET;
    }
    log.msg("Client Accepted");

}

int Socket::Request() {
    char buffer[10000] = { 0 };

    int received_bytes = recv(this->client, buffer, 10000, 0);
    if (received_bytes == 0) {
        log.msg("Connection Closed..");
    }
    else if (received_bytes < 0) {
        log.msg("Error in Receiving Data");
    }
    else {
        // Here call the reqeuest Parser
        m_pRequestParser = new RequestParser(buffer);
        log.msg("New Request : " + m_pRequestParser->getPath());
    }
    return received_bytes;
}

int Socket::SendResponse() {
    log.msg("Sending Response Now...");
    m_pResponse = new Response();
    std::string message = m_pResponse->getResponse(m_pRequestParser->getPath());

    return send(this->client, message.c_str(), (int)strlen(message.c_str()), 0);
}

void Socket::closeClient() {
    log.msg("Closing Socket Now...");
    closesocket(this->client);
}

server::Socket* server::CreateServer(int VERSION, int CONNECTION_TYPE, int PROTOCOL, std::string IP, int PORT) {
    Socket* sock = new Socket(VERSION, CONNECTION_TYPE, PROTOCOL, IP, PORT);
    sock->createSocket();
    sock->bindSocket();
    sock->listenConnection();
    return sock;

}

