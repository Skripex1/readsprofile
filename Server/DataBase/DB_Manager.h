// Created by Marius on 10/01/2024.

#ifndef SERVER_DB_MANAGER_H
#define SERVER_DB_MANAGER_H

#include <iostream>
#include <string>
#include <fstream>
#include <unordered_set>
#include "nlohmann/json.hpp"
#include "../utils/utils.h"

class DB_Manager {

public:



    static bool verify_account(const std::string &filePath, const std::string &username, const std::string &password);


    static bool new_account(const std::string &filePath, const std::string &username, const std::string &password);


    static bool delete_account(const std::string &filePath, const std::string &username);

    static std::vector<Book>
    search_book(const std::string &filePath, RequestType criteria, const std::string &searchValue);

    static bool
    updateSearchHistory(const std::string &filePath, const std::string &username, int bookID, double rating);

    static std::vector<Book> recommendBooks(const std::string &filePath, const std::string &currentUsername);

    static std::string getDownloadLink(const std::string &filePath, const int &bookId);

    static void delete_history (const std::string & filePath, const std::string& username);
};

#endif //SERVER_DB_MANAGER_H
