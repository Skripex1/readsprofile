//
// Created by Marius on 11/12/2023.
//
#include "TCPClient.h"

TCPClient::TCPClient(int connection_fd) : connfd(connection_fd) {};

TCPClient::~TCPClient() {
    close(connfd);
}

void TCPClient::send_message(const std::string &message) {
    write(connfd, message.c_str(), message.size());
}

std::string TCPClient::receive_message() {
    char buffer[MAX_SIZE];
    ssize_t buffer_bytes = read(connfd, buffer, sizeof(buffer));
    if (buffer_bytes < 0) {
        perror("Error at reading data.");
        exit(EXIT_FAILURE);
    }
    buffer[buffer_bytes] = '\0';
    std::string received_message(buffer);
    return received_message;
}

void TCPClient::handle_client() {
    TypeRequests typeRequests;

    while (1) {
        std::string message = receive_message();
        if (message.empty())
            break;
        std::cout << "Received from client : " << message << "\n";
        RequestType request = utils::getRequestType(message);
        switch (request) {
            case RequestType::LOGIN: {
                std::cout << "Login request detected...\n";
                try {

                    std::string information = utils::getInformation(message);
//                    std::cout << information << "\n";
                    if (typeRequests.login(information)) {
                        Account _account = utils::getAccount(information);
                        typeRequests.login_success(_account.user, _account.password);
                        std::cout << "Login successful, welocome " << typeRequests.getUsername() << "\n";
                        send_message("true");
                    } else {
                        std::cout << "Login failed !\n";
                        send_message("false");
                    }
                } catch (const std::invalid_argument &e) {
                    std::cerr << "Error: " << e.what() << '\n';
                    // Handle the error, such as sending a failure message to the client
                }
                break;
            }
            case RequestType::NEW_ACCOUNT: {
                std::cout << "New account request detected...\n";
                try {
                    std::string information = utils::getInformation(message);
                    if (typeRequests.newAccount(information)) {
                        std::cout << "Account created sucessfully ! \n";
                        send_message("true");
                    } else {
                        std::cout << "Account creation failed ! \n";
                        send_message("false");
                    }
                } catch (const std::invalid_argument &e) {
                    std::cerr << "Error: " << e.what() << '\n';
                    // Handle the error, such as sending a failure message to the client
                }
                break;
            }
            case RequestType::SEARCH_GENRE: {
                std::cout << "Search by genre request detected ...\n";
                std::string information = utils::getInformation(message);
                std::vector<Book> fetchedBooks = typeRequests.search_genre(information);
                std::string stringBooks = utils::booksToString(fetchedBooks);
                send_message(stringBooks);
                break;
            }
            case RequestType::SEARCH_TITLE: {
                std::cout << "Search by title request detected ...\n";
                std::string information = utils::getInformation(message);
                std::vector<Book> fetchedBooks = typeRequests.search_title(information);
                std::string stringBooks = utils::booksToString(fetchedBooks);
                send_message(stringBooks);
                break;
            }
            case RequestType::SEARCH_YEAR: {
                std::cout << "Search by year request detected ...\n";
                std::string information = utils::getInformation(message);
                std::vector<Book> fetchedBooks = typeRequests.search_year(information);
                std::string stringBooks = utils::booksToString(fetchedBooks);
                send_message(stringBooks);
                break;
            }
            case RequestType::SEARCH_AUTHOR: {
                std::cout << "Search by author request detected ...\n";
                std::string information = utils::getInformation(message);
                std::vector<Book> fetchedBooks = typeRequests.search_author(information);
                std::string stringBooks = utils::booksToString(fetchedBooks);
                send_message(stringBooks);
                break;
            }
            case RequestType::SEARCH_ISBN: {
                std::cout << "Search by ISBN request detected ...\n";
                std::string information = utils::getInformation(message);
                std::vector<Book> fetchedBooks = typeRequests.search_ISBN(information);
                std::string stringBooks = utils::booksToString(fetchedBooks);
                send_message(stringBooks);
                break;
            }
            case RequestType::SEARCH_RATING: {
                std::cout << "Search by rating request detected ...\n";
                std::string information = utils::getInformation(message);
                std::vector<Book> fetchedBooks = typeRequests.search_rating(information);
                std::string stringBooks = utils::booksToString(fetchedBooks);
                send_message(stringBooks);
                break;
            }
            case RequestType::UPDATE_HSTR: {
                std::cout << "Update history request detected ... \n";
                std::string information = utils::getInformation(message);
                std::cout << information << "\n";
                Query updateHstr = utils::user_search(message);
                std::cout << updateHstr.bookId << "" << updateHstr.bookId;
                if (typeRequests.rate_book(updateHstr.rating, updateHstr.bookId))
                    send_message("Accepted");
                else
                    send_message("Failed");
                break;
            }
            case RequestType::GENERATE_BOOKS: {
                std::cout << "Generate books request detected ...\n";
                std::string information = utils::getInformation(message);
                std::vector<Book> fetchedBooks = typeRequests.generateRecs();
                std::string stringBooks = utils::booksToString(fetchedBooks);
                send_message(stringBooks);
                break;
            }
            case RequestType::DOWNLOAD_BOOK: {
                std::cout << "Download book request detected ...\n";
                std::string information = utils::getInformation(message);
                std::string download_link = typeRequests.getDownloadLink(std::stoi(information));
                send_message(download_link);
                break;
            }
            case RequestType::DELETE_HSTR: {
                std::cout<< "Delete history request detected ... \n ";
                std::string information = utils::getInformation(message);
                typeRequests.delete_hstr();
                send_message("True");
                break;
            }
            case RequestType::UNKNOWN: {
                std::cout << "UNKNOWN";
                break;
            }
        }

        std::cout << "Server sent : Accepted\n";
    }
}
