#include "DB_Manager.h"
#include <fstream>
#include <stdexcept>

// ... [Previous class definition]

bool DB_Manager::verify_account(const std::string &filePath, const std::string &username, const std::string &password) {
    std::ifstream file(filePath);
    if (!file.is_open()) {
        return false;
    }

    nlohmann::json j;
    if (file.peek() != std::ifstream::traits_type::eof()) {
        file >> j;
    } else {
        return false;
    }

    for (const auto &user: j["users"]) {
        if (user["username"] == username && user["password"] == password) {
            return true;
        }
    }
    return false;
}


bool DB_Manager::new_account(const std::string &filePath, const std::string &username, const std::string &password) {
    std::ifstream file(filePath);
    if (!file.is_open()) {
        return false;
    }

    nlohmann::json j;
    if (file.peek() != std::ifstream::traits_type::eof()) {
        file >> j;
    } else {
        j = nlohmann::json::array();
    }
    file.close();
    for (const auto &user: j["users"]) {
        if (user["username"] == username) {
            return false;
        }
    }

    nlohmann::json newUser = {{"username", username},
                              {"password", password}};
    j["users"].push_back(newUser);

    std::ofstream outputFile(filePath);
    if (!outputFile) {
        return false;
    }
    outputFile << j.dump(4);
    outputFile.close();
    return true;
}


bool DB_Manager::delete_account(const std::string &filePath, const std::string &username) {
    std::ifstream file(filePath);
    if (!file.is_open()) {
        return false;
    }

    nlohmann::json j;
    if (file.peek() != std::ifstream::traits_type::eof()) {
        file >> j;
    } else {
        return false;
    }
    file.close();

    auto &users = j["users"];
    auto originalSize = users.size();
    users.erase(std::remove_if(users.begin(), users.end(), [&username](const nlohmann::json &user) {
        return user["username"] == username;
    }), users.end());

    if (users.size() == originalSize) {
        return false;
    }

    std::ofstream outputFile(filePath);
    if (!outputFile) {
        return false;
    }
    outputFile << j.dump(4);
    outputFile.close();
    return true;
}

std::vector<Book>
DB_Manager::search_book(const std::string &filePath, RequestType criteria, const std::string &searchValue) {
    std::vector<Book> matchingBooks;
    std::ifstream file(filePath);
    if (!file.is_open()) {
        throw std::runtime_error("Unable to open file: " + filePath);
    }

    nlohmann::json j;
    file >> j;

    int yearValue;
    double ratingValue;
    if (criteria == RequestType::SEARCH_YEAR) {
        yearValue = std::stoi(searchValue);
    } else if (criteria == RequestType::SEARCH_RATING) {
        ratingValue = std::stod(searchValue);
    }

    for (const auto &item: j["books"]) {
        Book book = utils::jsonToBook(item);

        switch (criteria) {
            case RequestType::SEARCH_GENRE:
                if (utils::fuzzyMatch(book.genres, searchValue, 3)) {
                    matchingBooks.push_back(book);
                }
                break;
            case RequestType::SEARCH_TITLE:
                if (utils::fuzzyMatch(book.title, searchValue, 3)) {
                    matchingBooks.push_back(book);
                }
                break;
            case RequestType::SEARCH_AUTHOR:
                if (utils::fuzzyMatch(book.author, searchValue, 3)) {
                    matchingBooks.push_back(book);
                }
                break;
            case RequestType::SEARCH_YEAR:
                if (std::abs(book.year - yearValue) <= 100) {
                    matchingBooks.push_back(book);
                }
                break;
            case RequestType::SEARCH_RATING:
                if (std::abs(book.rating - ratingValue) <= 0.5) {
                    matchingBooks.push_back(book);
                }
                break;
            case RequestType::SEARCH_ISBN:
                if (utils::fuzzyMatch(book.ISBN, searchValue, 3)) {
                    matchingBooks.push_back(book);
                }
                break;
            default:
                break;
        }
    }

    return matchingBooks;
}

bool
DB_Manager::updateSearchHistory(const std::string &filePath, const std::string &username, int bookID, double rating) {

    std::ifstream file(filePath);
    if (!file.is_open()) {
        return false;
    }

    nlohmann::json searchHistoryJson;
    if (file.peek() != std::ifstream::traits_type::eof()) {
        file >> searchHistoryJson;
    } else {
        return false;
    }
    file.close();


    auto &histories = searchHistoryJson["searchHistory"];
    auto it = std::find_if(histories.begin(), histories.end(), [&username](const nlohmann::json &history) {
        return history["username"] == username;
    });

    if (it != histories.end()) {

        it->at("searches").push_back({{"bookID", bookID},
                                      {"rating", rating}});
    } else {

        histories.push_back({
                                    {"username", username},
                                    {"searches", {{{"bookID", bookID}, {"rating", rating}}}}
                            });
    }


    std::ofstream outputFile(filePath);
    if (!outputFile) {
        return false;
    }
    outputFile << searchHistoryJson.dump(4);
    outputFile.close();
    return true;
}

std::vector<Book> DB_Manager::recommendBooks(const std::string &filePath, const std::string &currentUsername) {
    std::vector<Book> recommendedBooks;
    std::unordered_map<int, Book> bookMap;
    std::string favoriteGenres;
    std::ifstream file(filePath);
    nlohmann::json data;
    file >> data;
    file.close();

    for (const auto &item: data["books"]) {
        Book book = {
                item["ID"],
                item["title"],
                item["author"],
                item["year"],
                item["ISBN"],
                item["rating"],
                item["genres"]
        };
        bookMap[book.ID] = book;
    }

    for (const auto &user: data["searchHistory"]) {
        if (user["username"] == currentUsername) {
            for (const auto &search: user["searches"]) {
                if (search["rating"] >= 3.5) {
                    int bookID = search["bookID"];
                    favoriteGenres += bookMap[bookID].genres + ",";
                }
            }
            break;
        }
    }

    int count = 0;
    for (const auto &bookPair: bookMap) {
        if (utils::haveCommonGenres(favoriteGenres, bookPair.second.genres)) {
            recommendedBooks.push_back(bookPair.second);
            if (++count >= 4) break;
        }
    }

    for (const auto &user: data["searchHistory"]) {
        if (user["username"] != currentUsername) {
            int bookID = user["searches"][0]["bookID"];
            recommendedBooks.push_back(bookMap[bookID]);
            break;
        }
    }
    return recommendedBooks;
}

std::string DB_Manager::getDownloadLink(const std::string &filePath, const int &bookId) {
    std::ifstream file(filePath);
    nlohmann::json data;
    file >> data;
    file.close();

    for (const auto &book: data["books"]) {
        if (book["ID"] == bookId) {
            return book["download_link"];
        }
    }

    return "";
}

void DB_Manager::delete_history(const std::string &filePath, const std::string &username) {
    std::ifstream file(filePath);
    nlohmann::json data;
    file >> data;
    file.close();

    if (data.contains("searchHistory") && data["searchHistory"].is_array()) {
        for (auto it = data["searchHistory"].begin(); it != data["searchHistory"].end();) {
            if ((*it)["username"] == username) {
                it = data["searchHistory"].erase(it); // Erase user's search history
            } else {
                ++it;
            }
        }
    }

    std::ofstream outFile(filePath);
    outFile << data.dump(4);
    outFile.close();
}




