//
// Created by Marius on 11/01/2024.
//

#include "utils.h"
#include <iostream>

RequestType utils::getRequestType(const std::string &message) {
    size_t poz = message.find('$');
    std::string req;
    if (poz != std::string::npos)
        req = message.substr(0, poz);
    else
        req = message;
//    std::cout<<req<<"\n";
    if (req == "login") {
        return RequestType::LOGIN;
    } else if (req == "newacc") {
        return RequestType::NEW_ACCOUNT;
    } else if (req == "search1") {
        return RequestType::SEARCH_GENRE;
    } else if (req == "search3") {
        return RequestType::SEARCH_TITLE;
    } else if (req == "search2") {
        return RequestType::SEARCH_YEAR;
    } else if (req == "search4") {
        return RequestType::SEARCH_AUTHOR;
    } else if (req == "search5") {
        return RequestType::SEARCH_ISBN;
    } else if (req == "search6") {
        return RequestType::SEARCH_RATING;
    } else if (req == "update") {
        return RequestType::UPDATE_HSTR;
    } else if (req == "gen") {
        return  RequestType::GENERATE_BOOKS;
    }
    else if (req == "download") {
        return RequestType::DOWNLOAD_BOOK;
    }
    else if (req == "delete") {
        return  RequestType::DELETE_HSTR;
    }
    else {
        return RequestType::UNKNOWN;
    }
}

std::string utils::getInformation(const std::string &message) {
    size_t poz = message.find('$');
    if (poz != std::string::npos) {
        return message.substr(poz + 1);
    }
    return "";
}

Account utils::getAccount(const std::string &message) {
//    std::cout<<message<<"\n";
    size_t poz = message.find('.');
    if (poz != std::string::npos && poz + 1 < message.size()) {
        std::string _usr = message.substr(0, poz);
        std::string _psw = message.substr(poz + 1);
        std::cout << _usr << " " << _psw << "\n";
        return {_usr, _psw};
    }

    throw std::invalid_argument("Invalid account format.");
}

Book utils::jsonToBook(const nlohmann::json &j) {
    Book book;
    book.ID = j.at("ID").get<int>();
    book.title = j.at("title").get<std::string>();
    book.author = j.at("author").get<std::string>();
    book.year = j.at("year").get<int>();
    book.ISBN = j.at("ISBN").get<std::string>();
    book.rating = j.at("rating").get<double>();
    book.genres = j.at("genres").get<std::string>();
    return book;

}

std::string utils::booksToString(const std::vector<Book> &books) {
    std::string result;
    for (const auto &book: books) {
        result += "id:" + std::to_string(book.ID) + ",";
        result += "title:" + book.title + ",";
        result += "author:" + book.author + ",";
        result += "year:" + std::to_string(book.year) + ",";
        result += "ISBN:" + book.ISBN + ",";
        result += "rating:" + std::to_string(book.rating) + ",";
        result += "genres:" + book.genres + ";";
    }
    return result;
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


std::string utils::searchType(const std::string &message) {
    size_t poz = message.find(':');
    if (poz != std::string::npos) {
        return message.substr(poz + 1);
    }
    return "";
}

bool utils::fuzzyMatch(const std::string &str1, const std::string &str2, int threshold) {
    int matchCount = 0;
    for (size_t i = 0; i < std::min(str1.length(), str2.length()); ++i) {
        if (tolower(str1[i]) == tolower(str2[i])) {
            matchCount++;
        }
    }
    return matchCount >= threshold;
}

Query utils::user_search(const std::string &message) {
    size_t updatePos = message.find("update$");
    std::string processedMessage = (updatePos != std::string::npos) ? message.substr(updatePos + 7) : message;

    size_t poz = processedMessage.find('/');
    if (poz != std::string::npos && poz + 1 < processedMessage.size()) {
        std::string bookId = processedMessage.substr(0, poz);
        std::string rating = processedMessage.substr(poz + 1);

        int _bookId;
        double _rating;

        try {
            _bookId = std::stoi(bookId);
            _rating = std::stod(rating);
        } catch (const std::invalid_argument &e) {
            throw std::invalid_argument("Invalid format in message: " + processedMessage);
        } catch (const std::out_of_range &e) {
            throw std::out_of_range("Value out of range in message: " + processedMessage);
        }

        return {_bookId, _rating};
    } else {
        throw std::invalid_argument("Invalid format: " + processedMessage);
    }
}

bool utils::haveCommonGenres(const std::string &userGenres, const std::string &bookGenres) {
    std::istringstream userStream(userGenres);
    std::string genre;
    while (getline(userStream, genre, ',')) {
        if (bookGenres.find(genre) != std::string::npos) {
            return true;
        }
    }
    return false;
}


