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
#define MAX_SIZE 2048
#include "../TypeRequests/TypeRequests.h"
#include "../utils/utils.h"
class TCPClient {
private:
    int connfd;
public:
    TCPClient(int connection_fd);
    ~TCPClient();
    void send_message(const std::string & message);
    std::string receive_message();
    void handle_client();
};


#endif //SERVER_TCPCLIENT_H
