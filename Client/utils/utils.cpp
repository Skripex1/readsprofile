//
// Created by Marius on 11/01/2024.
//

#include "utils.h"
#include <algorithm>
#include <iostream>
#include <sstream>

bool utils::stringToBool(const std::string &myString) {
    std::string lowerStr = myString;
    std::transform(lowerStr.begin(), lowerStr.end(), lowerStr.begin(), ::tolower);
    return lowerStr == "true";
}

void utils::Interface_NotAuth() {
    std::cout << "Please choose one of the following : \n";
    std::cout << "1.Log In \n";
    std::cout << "2.New Account \n";
    std::cout << "3.Exit \n";
}

Account utils::getCredentials() {
    std::cout << "Username: \n";
    std::string _username;
    std::cin >> _username;
    std::cout << "Password: \n";
    std::string _password;
    std::cin >> _password;
    return {_username, _password};
}

void utils::Interface_Auth() {
    std::cout << "Please choose one of the following : \n";
    std::cout << "1. Search book by genre \n";
    std::cout << "2. Search book by year\n";
    std::cout << "3. Search book by title \n";
    std::cout << "4. Search book by author \n";
    std::cout << "5. Search book by ISBN \n";
    std::cout << "6. Search book by rating \n";
    std::cout << "7. Recommended books for you \n";
    std::cout << "8. Rate book (by ID) \n";
    std::cout << "9.Get download link (by ID) \n";
    std::cout << "10.Delete history \n";
    std::cout << "11. Log out \n";
    std::cout << "12. Exit \n";

}

std::vector<Book> utils::stringToBooks(const std::string &str) {
    std::vector<Book> books;
    std::istringstream bookStream(str);
    std::string bookStr;

    while (std::getline(bookStream, bookStr, ';')) {
        std::istringstream fieldStream(bookStr);
        std::string field;
        Book book;

        while (std::getline(fieldStream, field, ',')) {
            auto delimiterPos = field.find(':');
            auto key = field.substr(0, delimiterPos);
            auto value = field.substr(delimiterPos + 1);

            if (key == "id") {
//                std::cout << "Converting value" << value;
                book.ID = std::stoi(value);
            } else if (key == "title") book.title = value;
            else if (key == "author") book.author = value;
            else if (key == "year") book.year = std::stoi(value);
            else if (key == "ISBN") book.ISBN = value;
            else if (key == "rating") book.rating = std::stod(value);
            else if (key == "genres") book.genres = value;
        }

        books.push_back(book);
    }

    return books;
}

void utils::showBooks(const std::vector<Book> &books) {
    int size = books.size();
    if (size == 0) {
        std::cout << "Couldn't find anything ! \n";
        return;
    }

    int i = 0;
    while (i < size && i <= 3) {
        showBook(books[i]);
        nextexitrate();
        int option;
        std::cin >> option;
        if (option == 1)
            i++;
        if (option == 2)
            break;

    }
}

void utils::showBook(const Book &book) {
    std::cout << "Book Id: " << book.ID << "\n";
    std::cout << "Title : " << book.title << "\n";
    std::cout << "Author : " << book.author << "\n";
    std::cout << "Genres: " << book.genres << "\n";
    std::cout << "Rating: " << book.rating << "\n";
    std::cout << "Year: " << book.year << "\n";
    std::cout << "ISBN: " << book.ISBN << "\n";
}

void utils::nextexitrate() {
    std::cout << "1.Next option\n";
    std::cout << "2.Back to menu\n";
}
