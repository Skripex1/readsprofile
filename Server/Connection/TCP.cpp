//
// Created by Marius on 11/12/2023.
//

#include "TCP.h"

TCP::TCP() {
    sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if (sockfd == -1) {
        perror("Socket creation failed.");
        exit(EXIT_FAILURE);
    }
}

TCP::~TCP() {
    close(sockfd);
}

void TCP::establish_tcp_connection() {
    struct sockaddr_in server_addr;
    std::cout << "Server started...\n";

    for (int port = startPort; port <= endPort; ++port) {
        bzero(&server_addr, sizeof(server_addr));
        server_addr.sin_family = AF_INET;
        server_addr.sin_addr.s_addr = htonl(INADDR_ANY);
        server_addr.sin_port = htons(port);

        if (bind(sockfd, (struct sockaddr *)&server_addr, sizeof(server_addr)) == 0) {
            std::cout << "Successfully bound to port " << port << std::endl;
            return; // Successfully bound
        }

        if (errno != EADDRINUSE) {
            perror("Socket bind failed.");
            exit(EXIT_FAILURE); // Exit if failure is not due to EADDRINUSE
        }
    }

    std::cerr << "Failed to bind within the port range." << std::endl;
    exit(EXIT_FAILURE); // No ports available in range
}

void TCP::start_listening() {
    if (listen(sockfd, 10) != 0) {
        perror("Listen failed.");
        exit(EXIT_FAILURE);
    }
    while (true) {
        socklen_t client_length = sizeof(struct sockaddr_in);
        int connfd = accept(sockfd, nullptr, &client_length);
        if (connfd < 0) {
            perror("Server accept failed.");
            exit(EXIT_FAILURE);
        }

        pid_t pid = fork();

        if (pid < 0) {
            perror("Fork failed.");
            exit(EXIT_FAILURE);
        } else if (pid == 0) {
            close(sockfd);
            TCPClient client_handler(connfd);
            client_handler.handle_client();
            exit(EXIT_SUCCESS);
        } else {
            close(connfd);
            waitpid(-1, nullptr, WNOHANG);
        }
    }
}
