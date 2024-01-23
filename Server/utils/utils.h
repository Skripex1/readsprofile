//
// Created by Marius on 11/01/2024.
//

#ifndef SERVER_UTILS_H
#define SERVER_UTILS_H

#include "../DataBase/nlohmann/json.hpp"
#include <string>
#include <fstream>
#include <unordered_set>

const std::string filePath = "../DataBase/DataBase.json";

enum class RequestType {
    LOGIN,
    LOGOUT,
    NEW_ACCOUNT,
    SEARCH_GENRE,
    SEARCH_TITLE,
    SEARCH_YEAR,
    SEARCH_RATING,
    SEARCH_ISBN,
    SEARCH_AUTHOR,
    UPDATE_HSTR,
    GENERATE_BOOKS,
    DOWNLOAD_BOOK,
    DELETE_HSTR,
    UNKNOWN
};

struct Account{
    std::string user;
    std::string password;
};

struct Book {
    int ID;
    std::string title;
    std::string author;
    int year;
    std::string ISBN;
    double rating;
    std::string genres;
};

struct Query {
    int bookId;
    double rating;
};


class utils {
public:
    static RequestType getRequestType(const std::string& message);
    static std::string getInformation(const std::string& message);
    static Account getAccount(const std::string& message);
    static Book jsonToBook (const nlohmann::json&j);
    static std::string booksToString(const std::vector<Book>&books);
    static std::vector<Book> stringToBooks (const std::string & str);
    static std::string searchType (const std::string &message);
    static Query user_search (const std::string &message);
    static bool fuzzyMatch(const std::string &str1, const std::string &str2, int threshold);
    static bool haveCommonGenres(const std::string& userGenres, const std::string& bookGenres);
};


#endif //SERVER_UTILS_H
