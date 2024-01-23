//
// Created by Marius on 11/12/2023.
//

#ifndef SERVER_TCPCLIENT_H
#define SERVER_TCPCLIENT_H

#include <stdio.h>
#include <netdb.h>
#include <netinet/in.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <unistd.h>
#include <iostream>
#include <string>
#include <arpa/inet.h>

#define MAX_SIZE 2048
#define PORT 8080

class TCPClient {
private:
    int sockfd;
public:
    TCPClient();

    ~TCPClient();

    void establish_tcp_connection();

    void send_message(const std::string &message);

    std::string receive_message();
};


#endif //SERVER_TCPCLIENT_H
