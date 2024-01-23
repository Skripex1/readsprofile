//
// Created by Marius on 11/01/2024.
//

#ifndef CLIENT_UTILS_H
#define CLIENT_UTILS_H

#include <string>
#include <vector>
struct Account {
    std::string username;
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

class utils {
public:
    static bool stringToBool(const std::string &myString);

    static void Interface_NotAuth();

    static Account getCredentials();

    static void Interface_Auth();

    static std::vector<Book> stringToBooks(const std::string &str);

    static void showBooks(const std::vector<Book> &books);

    static void showBook(const Book &book);

    static void nextexitrate();

    static std::string exchange (const std::string& msg);
};


#endif //CLIENT_UTILS_H
