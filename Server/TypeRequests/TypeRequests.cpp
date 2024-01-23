//
// Created by Marius on 11/01/2024.
//

#include "TypeRequests.h"


bool TypeRequests::login(const std::string &credentials) {
    Account getAccount = utils::getAccount(credentials);
    return DB_Manager::verify_account(filePath, getAccount.user, getAccount.password);
}

bool TypeRequests::newAccount(const std::string &credentials) {
    Account getAccount = utils::getAccount(credentials);
    return DB_Manager::new_account(filePath, getAccount.user, getAccount.password);
}

std::vector<Book> TypeRequests::search_genre(const std::string &value) {
    return DB_Manager::search_book(filePath, RequestType::SEARCH_GENRE, value);
}

std::vector<Book> TypeRequests::search_title(const std::string &value) {
    return DB_Manager::search_book(filePath, RequestType::SEARCH_TITLE, value);
}

std::vector<Book> TypeRequests::search_year(const std::string &value) {
    return DB_Manager::search_book(filePath, RequestType::SEARCH_YEAR, value);
}

std::vector<Book> TypeRequests::search_rating(const std::string &value) {
    return DB_Manager::search_book(filePath, RequestType::SEARCH_RATING, value);
}

std::vector<Book> TypeRequests::search_author(const std::string &value) {
    return DB_Manager::search_book(filePath, RequestType::SEARCH_AUTHOR, value);
}

std::vector<Book> TypeRequests::search_ISBN(const std::string &value) {
    return DB_Manager::search_book(filePath, RequestType::SEARCH_ISBN, value);
}

bool TypeRequests::rate_book(const double &rating, const int &bookId) {
    return DB_Manager::updateSearchHistory(filePath, account.user, bookId, rating);
}

void TypeRequests::login_success(const std::string &username, const std::string &password) {
    account.user = username;
    account.password = password;
    isAuthenticated = true;
}

void TypeRequests::logout() {
    account.user = "";
    account.password = "";
    isAuthenticated = false;
}

bool TypeRequests::isLogged() {
    return isAuthenticated;
}

std::string TypeRequests::getUsername() {
    return account.user;
}

std::string TypeRequests::getPassword() {
    return account.password;
}

std::vector<Book> TypeRequests::generateRecs() {
    return DB_Manager::recommendBooks(filePath, account.user);
}

std::string TypeRequests::getDownloadLink(const int &bookId) {
    return DB_Manager::getDownloadLink(filePath,bookId);
}

void TypeRequests::delete_hstr() {
    DB_Manager::delete_history(filePath,account.user);
}








