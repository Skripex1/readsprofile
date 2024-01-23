//
// Created by Marius on 11/12/2023.
//

#ifndef SERVER_TCP_H
#define SERVER_TCP_H
#include "TCPClient.h"
#include <stdio.h>
#include <netdb.h>
#include <netinet/in.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <unistd.h>
#include <sys/wait.h>
#define MAX_SIZE 2048
#include <string>
#include <iostream>
#define PORT 8080

class TCP {
private:
    int  sockfd;
    const int startPort = 49152;
    const int endPort = 49161;
public:
    TCP();
    ~TCP();
    void establish_tcp_connection();
    void start_listening();
};


#endif //SERVER_TCP_H
