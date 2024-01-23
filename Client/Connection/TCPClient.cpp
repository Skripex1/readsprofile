//
// Created by Marius on 11/12/2023.
//

#include "TCPClient.h"


TCPClient::TCPClient() : sockfd(socket(AF_INET, SOCK_STREAM, 0)) {
    if (sockfd == -1) {
        perror("Socket creation failed.");
        exit(EXIT_FAILURE);
    }
}

TCPClient::~TCPClient() {
    close(sockfd);
}

void TCPClient::establish_tcp_connection() {
    struct sockaddr_in server_addr;
    bzero(&server_addr, sizeof(server_addr));
    server_addr.sin_family = AF_INET;
    server_addr.sin_addr.s_addr = inet_addr("127.0.0.1");

    const int startPort = 49152; // Start of the port range
    const int endPort = 49161;   // End of the port range

    for (int port = startPort; port <= endPort; ++port) {
        server_addr.sin_port = htons(port);

        if (connect(sockfd, (struct sockaddr *) &server_addr, sizeof(server_addr)) == 0) {
            std::cout << "Connected to server on port " << port << std::endl;
            return; // Successfully connected
        }

        // If connection failed, try the next port
        if (errno != ECONNREFUSED) {
            perror("Connection to server failed.");
            exit(EXIT_FAILURE); // Exit if failure is not due to ECONNREFUSED
        }
    }

    std::cerr << "Failed to connect within the port range." << std::endl;
    exit(EXIT_FAILURE); // No successful connection in range
}

void TCPClient::send_message(const std::string &message) {
    write(sockfd, message.c_str(), message.size());
}

std::string TCPClient::receive_message() {
    char buffer[MAX_SIZE];
    ssize_t buffer_bytes = read(sockfd, buffer, sizeof(buffer));
    if (buffer_bytes < 0) {
        perror("Error at reading data.");
        exit(EXIT_FAILURE);
    }
    buffer[buffer_bytes] = '\0';
    std::string received_message(buffer);
    return received_message;
}
