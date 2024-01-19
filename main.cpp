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

    sockaddr_in clientService{};
    clientService.sin_family = AF_INET;

    InetPton(AF_INET, "127.0.0.1", &clientService.sin_addr.s_addr);
    clientService.sin_port = htons(8080);

    auto clientSocket = INVALID_SOCKET;

    clientSocket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);

    if (clientSocket == INVALID_SOCKET){
         std::cerr << "[ERROR] Socket Error: " <<  WSAGetLastError() <<  std::endl;
        WSACleanup();
        return 1;
    }

    if (connect(clientSocket, reinterpret_cast<SOCKADDR *>(&clientService), sizeof(clientService)) == SOCKET_ERROR){
         std::cerr << "[ERROR] Client: Failed to connect.\n";
        WSACleanup();
        return 1;
    }

     std::cout << "[INFO] Client: Successfully Connection.\n[INFO] Client: Can start sending and receiving data...\n";


    std::cout << "Winsock Blogging\nPick An Option:\n 1 - Login\n 2 - Register\n 3 - Quit\nInput Selection:" << std::endl;



    User* user = nullptr;


    while (user == nullptr) {

        char* option = nullptr;
        std::cin >> option;
        switch (option) {
            case "1":
                try {
                    user = User::login(&clientSocket);

                    std::cout << "Successfully Logged In" << std::endl;
                }
                catch (ClientException &ex) {
                    std::cout << "Error Occurred: " << ex.description << ", Code: " << ex.code << std::endl;
                }
                break;
            case "2":
                try {
                    user = User::Register(&clientSocket);
                }
                catch (ClientException &ex) {
                    std::cout << "Error Occurred: " << ex.description << ", Code: " << ex.code << std::endl;
                }
            break;
            case "3":
                closesocket(clientSocket);
                WSACleanup();
                exit(0);
            break;
            default:
                std::cout << "Invalid Input Try Again" << std::endl;
            break;
        }
    }

    system("CLS");

    std::cout << "Winsock Blogging\nPick An Option:\n 1 - Send Blog Post\n 2 - Read Blog Posts\n 3 - Delete a Blog Post\n 4 - Quit\nInput Selection:" << std::endl;



    while (true) {
        char* cmdOption = nullptr;


        std::cout << "Input Option: " << std::endl;
        std::cin >> cmdOption;

        switch (cmdOption) {
            case "1":
                BlogPost post;
                char* desc = nullptr;
                std::cout << "Input Blog Description" << std::endl;
                std::cin >> desc;
                post.SetDescription(desc);
                char* title = nullptr;
                std::cout << "Input Blog Title" << std::endl;
                std::cin >> title;
                post.SetTitle(title);
                post.SendPost(clientSocket);
                break;
            case "2":
                BlogPost::ReadPosts(clientSocket);
            break;
            case "3":
                try {
                    char* deletion_title = nullptr;
                    std::cout << "Input Title To Deleted: " << std::endl;
                    std::cin >> deletion_title;
                    Admin::DeletePost(clientSocket, *user, deletion_title);
                }
                catch (ClientException &exception) {
                    std::cerr << exception.description << std::endl;
                }
            break;
            case "4":
                std::cout << "Exiting..." << std::endl;
                closesocket(clientSocket);
                WSACleanup();
                exit(0);
            break;
            default:
            break;
        }
    }

    closesocket(clientSocket);
    WSACleanup();



    return 0;
}