//
// Created by Marius on 11/01/2024.
//

#ifndef CLIENT_TYPEREQUESTS_H
#define CLIENT_TYPEREQUESTS_H

#include <iostream>
#include "../Connection/TCPClient.h"
#include "../utils/utils.h"

class TypeRequests {
private:
    bool isAuthenticated;
    TCPClient *client;
    Account account;
public:
    TypeRequests(TCPClient &_client);

    bool login(const std::string &username, const std::string &password);

    std::vector<Book> search_genre(const std::string &value);

    std::vector<Book> search_title(const std::string &value);

    std::vector<Book> search_year(const std::string &value);

    std::vector<Book> search_author (const std::string &value);

    std::vector<Book> search_isbn (const std::string &value);

    std::vector<Book> search_rating (const std::string &value);

    bool rate_search (const int& bookId , const double & rating);

    std::vector<Book> generate_books ();

    std::string download_book (const int& bookId);

    void delete_history ();

    bool newAccount(const std::string &username, const std::string &password);

    bool isLogged() {
        return isAuthenticated;
    }

    void login_sucessfull(const std::string &username, const std::string &password);

    void logout();

    std::string fetchUsername() {
        return account.username;
    }

    std::string fetchPassword() {
        return account.password;
    }
    TCPClient* fetchClient() {
        return client;
    }
};


#endif //CLIENT_TYPEREQUESTS_H
