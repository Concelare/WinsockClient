#include <iostream>
#include <winsock2.h>
#include <ws2tcpip.h>

#include "Admin.h"
#include "BlogPost.h"
#include "ClientException.h"
#include "User.h"


int main() {
    // Initialising & Setting Up wsaData with Version Number
    WSADATA wsaData;
    constexpr WORD wVersionRequested = MAKEWORD(2, 2);

    // Checks if it can find the Winsock.dll if it can't it closes the program with error code 1
    if (const int wsaerr = WSAStartup(wVersionRequested, &wsaData); wsaerr != 0) {
         std::cerr << "[ERROR] The Winsock.dll not found\n";
        return 1;
    }

    std::cout << "[INFO] Successfully Loaded Winsock.dll" << std::endl;

    // Initalise the clientService to store destination address & port
    sockaddr_in clientService{};
    clientService.sin_family = AF_INET;

    // Set the address for the clientService
    InetPton(AF_INET, "127.0.0.1", &clientService.sin_addr.s_addr);
    clientService.sin_port = htons(8080);

    // Initalises the clientSocket & sets it to an INVALID_SOCKET
    auto clientSocket = INVALID_SOCKET;

    // Sets up the clientSocket for tcp communication
    clientSocket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);

    // Check if the sockets setup failed
    if (clientSocket == INVALID_SOCKET){
         std::cerr << "[ERROR] Socket Error: " <<  WSAGetLastError() <<  std::endl;
        WSACleanup();
        return 1;
    }

    // Connect To The Server
    if (connect(clientSocket, reinterpret_cast<SOCKADDR *>(&clientService), sizeof(clientService)) == SOCKET_ERROR){
         std::cerr << "[ERROR] Client: Failed to connect.\n";
        WSACleanup();
        return 1;
    }

     std::cout << "[INFO] Client: Successfully Connection.\n[INFO] Client: Can start sending and receiving data...\n";


    std::cout << "Winsock Blogging\nPick An Option:\n 1 - Login\n 2 - Register\n 3 - Quit\nInput Selection:" << std::endl;


    // Initialise the User Pointer & set to null
    User* user = nullptr;

    // Run until the user is not a nullptr
    while (user == nullptr) {
        // Initialises the option
        char* option = nullptr;
        // Sets the option
        std::cin >> option;
        // Checks the option
        switch (option) {
            case "1":
                try {
                    // Sets the returned pointer to the user variable
                    user = User::login(&clientSocket);

                    std::cout << "[INFO] Successfully Logged In" << std::endl;
                }
                catch (ClientException &ex) {
                    // Outputs the error returned
                    std::cerr << "[Error] " << ex.description << ", Code: " << ex.code << std::endl;
                }
                break;
            case "2":
                try {
                    // Sets the returned pointer to the user variable
                    // Using a Function Pointer
                    User* (*fcnPtr)(const SOCKET*) { &User::Register };
                    user = (*fcnPtr)(&clientSocket);
                    std::cout << "[INFO] Successfully Registered" << std::endl;
                }
                catch (ClientException &ex) {
                    // Outputs the error returned
                    std::cerr << "[Error] " << ex.description << ", Code: " << ex.code << std::endl;
                }
            break;
            case "3":
                // Closes Socket, Winsock Cleansup then Exits
                closesocket(clientSocket);
                WSACleanup();
                exit(0);
            break;
            default:
                std::cout << "[Error] Invalid Input Try Again" << std::endl;
            break;
        }
    }

    system("CLS");

    std::cout << "Winsock Blogging\nPick An Option:\n 1 - Send Blog Post\n 2 - Read Blog Posts\n 3 - Delete a Blog Post\n 4 - Quit\nInput Selection:" << std::endl;


    // Loop till program exitted
    while (true) {
        // Initialises the cmdOption Pointer & sets to null
        char* option = nullptr;

        std::cout << "Input Option: " << std::endl;

        // Sets the cmdOption Value
        std::cin >> option;

        // Checks the cmdOption
        switch (option) {
            case "1":
                // Initialise Variables
                BlogPost post;
                char* desc = nullptr;
                char* title = nullptr;

                // Sets The Description of Post
                std::cout << "Input Blog Description" << std::endl;
                std::cin >> desc;
                post.SetDescription(desc);

                // Sets The Title of the Post
                std::cout << "Input Blog Title" << std::endl;
                std::cin >> title;
                post.SetTitle(title);

                // Sends the post
                post.SendPost(clientSocket);
                break;
            case "2":
                // Gets & Displays Posts
                BlogPost::ReadPosts(clientSocket);
            break;
            case "3":
                try {
                    // Initialises the deletion title & sets to null
                    char* deletion_title = nullptr;
                    // Sets the deletion title
                    std::cout << "Input Title To Deleted: " << std::endl;
                    std::cin >> deletion_title;
                    // Runs the deletepost function
                    Admin::DeletePost(clientSocket, *user, deletion_title);
                }
                catch (ClientException &exception) {
                    std::cerr << exception.description << std::endl;
                }
            break;
            case "4":
                std::cout << "Exiting..." << std::endl;
                // Disconnects Socket, Winsock clean up & Exit Program
                closesocket(clientSocket);
                WSACleanup();
                exit(0);
            break;
            default:
                std::cout << "[Error] Invalid Input Try Again" << std::endl;
            break;
        }
    }

    closesocket(clientSocket);
    WSACleanup();

    return 0;
}