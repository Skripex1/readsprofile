//
// Created by Marius on 11/01/2024.
//

#include "TypeRequests.h"
#include <iostream>

TypeRequests::TypeRequests(TCPClient &_client) {
    client = &_client;
    isAuthenticated = false;
}

bool TypeRequests::login(const std::string &username, const std::string &password) {
    std::string finalMessage = "login$" + username + "." + password;
    client->send_message(finalMessage);
    std::string received_message = client->receive_message();
    return utils::stringToBool(received_message);
}

bool TypeRequests::newAccount(const std::string &username, const std::string &password) {
    std::string message = "newacc$" + username + "." + password;
    std::cout << message << "\n";
    client->send_message(message);
    std::string received_message = client->receive_message();
    return utils::stringToBool(received_message);
}

void TypeRequests::login_sucessfull(const std::string &username, const std::string &password) {
    isAuthenticated = true;
    account.username = username;
    account.password = password;
}

void TypeRequests::logout() {
    account.username = "";
    account.password = "";
    isAuthenticated = false;
}

std::vector<Book> TypeRequests::search_genre(const std::string &value) {
    std::string message = "search1$" + value;
    client->send_message(message);
    std::string received_message = client->receive_message();
    return utils::stringToBooks(received_message);
}

std::vector<Book> TypeRequests::search_year(const std::string &value) {
    std::string message = "search2$" + value;
    client->send_message(message);
    std::string received_message = client->receive_message();
    return utils::stringToBooks(received_message);
}

std::vector<Book> TypeRequests::search_title(const std::string &value) {
    std::string message = "search3$" + value;
    client->send_message(message);
    std::string received_message = client->receive_message();
    return utils::stringToBooks(received_message);
}

std::vector<Book> TypeRequests::search_author(const std::string &value) {
    std::string message = "search4$" + value;
    client->send_message(message);
    std::string received_message = client->receive_message();
    return utils::stringToBooks(received_message);
}

std::vector<Book> TypeRequests::search_isbn(const std::string &value) {
    std::string message = "search5$" + value;
    client->send_message(message);
    std::string received_message = client->receive_message();
    return utils::stringToBooks(received_message);
}

std::vector<Book> TypeRequests::search_rating(const std::string &value) {
    std::string message = "search6$" + value;
    client->send_message(message);
    std::string received_message = client->receive_message();
    return utils::stringToBooks(received_message);
}

bool TypeRequests::rate_search(const int &bookId, const double &rating) {
    std::string message = "update$" + std::to_string(bookId) + "/" + std::to_string(rating);
    client->send_message(message);
    std::string received_message = client->receive_message();
    return true;
}

std::vector<Book> TypeRequests::generate_books() {
    std::string message = "gen$";
    client->send_message(message);
    std::string received_message = client->receive_message();
    return utils::stringToBooks(received_message);
}

std::string TypeRequests::download_book(const int &bookId) {
    std::string message = "download$"+std::to_string(bookId);
    client->send_message(message);
    std::string  received_message = client->receive_message();
    return  received_message;
}

void TypeRequests::delete_history() {
    std::string message = "delete$";
    client->send_message(message);
    std::string  received_message = client->receive_message();
}
