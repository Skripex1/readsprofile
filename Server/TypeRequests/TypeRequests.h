//
// Created by Marius on 11/01/2024.
//

#ifndef SERVER_TYPEREQUESTS_H
#define SERVER_TYPEREQUESTS_H

#include <string>
#include "../utils/utils.h"
#include "../DataBase/DB_Manager.h"


class TypeRequests {
private:
    bool isAuthenticated = false;
    Account account;
public:


    bool login(const std::string &credentials);

    bool newAccount(const std::string &credentials);

    void login_success(const std::string &username, const std::string &password);

    std::vector<Book> search_genre(const std::string &value);

    std::vector<Book> search_title(const std::string &value);

    std::vector<Book> search_year(const std::string &value);

    std::vector<Book> search_rating(const std::string &value);

    std::vector<Book> search_author(const std::string &value);

    std::vector<Book> search_ISBN(const std::string &value);

    bool rate_book(const double &rating, const int &bookId);

    std::string getDownloadLink (const int &bookId);

    void delete_hstr ();

    std::vector<Book> generateRecs ();

    void logout();

    bool isLogged();

    std::string getUsername();

    std::string getPassword();

};


#endif //SERVER_TYPEREQUESTS_H
