#include "Connection/TCPClient.h"
#include "Requests/TypeRequests.h"
#include "utils/utils.h"
#include <iostream>

int main() {
    TCPClient client;
    client.establish_tcp_connection();
    TypeRequests typeRequests(client);
    bool welcomeMsg = 1;
    while (1) {
        if (!typeRequests.isLogged()) {
            utils::Interface_NotAuth();
            int option;
            std::cin >> option;
            switch (option) {
                case 1: {
                    Account extAcc = utils::getCredentials();
                    if (typeRequests.login(extAcc.username, extAcc.password))
                        typeRequests.login_sucessfull(extAcc.username, extAcc.password);
                    else
                        std::cout << "Wrong credentials . Please try again . \n";
                    break;
                }
                case 2 : {
                    Account newAcc = utils::getCredentials();
                    if (typeRequests.newAccount(newAcc.username, newAcc.password)) {
                        std::cout << "Account created sucessfully ! \n";
                        typeRequests.login_sucessfull(newAcc.username, newAcc.password);
                    } else
                        std::cout << "Error at creating the account ! \n";
                    break;
                }
                case 3 : {
                    std::cout << "Goodbye ! \n";
                    return 0;
                }
                default:
                    break;
            }
        }
        if (typeRequests.isLogged()) {
            if (welcomeMsg)
                std::cout << "User authenticated sucessfully ! \n" << "Welcome " << typeRequests.fetchUsername()
                          << "\n", welcomeMsg = false;
            utils::Interface_Auth();
            int reqNr;
            std::cin >> reqNr;
            switch (reqNr) {
                case 1 : {
                    std::cout << "Genre to search : \n";
                    std::string genre;
                    std::cin >> genre;
                    std::vector<Book> fetchedBooks = typeRequests.search_genre(genre);
                    utils::showBooks(fetchedBooks);
                    break;
                }

                case 3: {
                    std::cout << "Title to search : \n";
                    std::string title;
                    std::cin >> title;
                    std::vector<Book> fetchedBooks = typeRequests.search_title(title);
                    utils::showBooks(fetchedBooks);
                    break;
                }
                case 2 : {
                    std::cout << "Year to search : \n";
                    std::string year;
                    std::cin >> year;
                    std::vector<Book> fetchedBooks = typeRequests.search_year(year);
                    utils::showBooks(fetchedBooks);
                    break;
                }
                case 4 : {
                    std::cout << "Author to search : \n";
                    std::string author;
                    std::cin >> author;
                    std::vector<Book> fetchedBooks = typeRequests.search_author(author);
                    utils::showBooks(fetchedBooks);
                    break;
                }
                case 5: {
                    std::cout << "ISBN to search : \n";
                    std::string isbn;
                    std::cin >> isbn;
                    std::vector<Book> fetchedBooks = typeRequests.search_isbn(isbn);
                    utils::showBooks(fetchedBooks);
                    break;
                }
                case 6: {
                    std::cout << "Rating to search : \n";
                    std::string rating;
                    std::cin >> rating;
                    std::vector<Book> fetchedBooks = typeRequests.search_rating(rating);
                    utils::showBooks(fetchedBooks);
                    break;
                }
                case 8 : {
                    std::cout<<"Choose a book ID : \n";
                    int bookId;
                    std::cin>>bookId;
                    std::cout<<"Choose a rating : \n";
                    double rating;
                    std::cin >>rating;
                    typeRequests.rate_search(bookId,rating);
                    break;
                }
                case 7 : {
                    std::vector<Book> fetchedBooks = typeRequests.generate_books();
                    utils::showBooks(fetchedBooks);
                    break;
                }
                case 9 :
                {
                    std::cout<<"Choose a book ID : \n";
                    int bookId;
                    std::cin>>bookId;
                    std::string fetchedDownloadLink = typeRequests.download_book(bookId);
                    std::cout<<"Link is ready ! "<<fetchedDownloadLink<<"\n";
                    break;
                }
                case 10 :
                    typeRequests.delete_history();
                    break;
                case 11 : {
                    std::cout<<"Logging out ... \n";
                    typeRequests.logout();
                    break;
                }
                case 12: {
                    std::cout<<"Goodbye ! \n";
                    return 0;
                }
                default:
                    break;
            }


        }

    }


    return 0;
}
