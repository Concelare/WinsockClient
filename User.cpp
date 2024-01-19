//
// Created by Ben on 02/01/2024.
//

#include "User.h"

#include <iostream>

#include "ClientException.h"
#include "Command.h"

User* User::login(const SOCKET* socket) {

    char* uname = nullptr;

    std::cout << "Username: " << std::endl;
    std::cin >> uname;

    char* passw = nullptr;

    std::cout << "Password: " << std::endl;
    std::cin >> passw;

    std::vector<char*> body;

    body.push_back(uname);
    body.push_back(passw);

    Command cmd = Command("Login", body);

    send(*socket, reinterpret_cast<char *>(&cmd), sizeof(cmd), 0);

    char receiveBuffer[200] = "";
    recv(*socket, receiveBuffer, 200, 0);

    if (strcmp(receiveBuffer, "Login Failed") != 0) {
        throw ClientException("Login Creditinals Are Incorrect", 0001);
    }


    User user {};

    user.SetUsername(uname);


    return &user;
}

User* User::Register(const SOCKET* socket) {

    char* uname = nullptr;

    std::cout << "Username: " << std::endl;
    std::cin >> uname;

    char* passw = nullptr;

    std::cout << "Password: " << std::endl;
    std::cin >> passw;

    std::vector<char*> body;

    body.push_back(uname);
    body.push_back(passw);

    Command cmd = Command("Register", body);

    send(*socket, reinterpret_cast<char *>(&cmd), sizeof(cmd), 0);

    char receiveBuffer[200] = "";
    recv(*socket, receiveBuffer, 200, 0);

    if (strcmp(receiveBuffer, "Register Failed") != 0) {
        throw ClientException("Failed To Register", 0002);
    }

    User user {};

    user.SetUsername(uname);


    return &user;
}

void User::SetUsername(char* uname) {
    this -> username = uname;
}

