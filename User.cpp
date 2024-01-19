//
// Created by Ben on 02/01/2024.
//

#include "User.h"

#include <iostream>

#include "ClientException.h"
#include "Command.h"


// User Login Function
User* User::login(const SOCKET* socket) {
    // Initialise Variables
    char* username = nullptr;
    char* password = nullptr;
    std::vector<char*> body;

    // Sets Username
    std::cout << "Username: " << std::endl;
    std::cin >> username;

    // Sets Password
    std::cout << "Password: " << std::endl;
    std::cin >> password;

    // Pushes Parameters into the command body
    body.push_back(username);
    body.push_back(password);

    // Constructs the command
    Command cmd = Command("Login", body);

    // Sends Command to Server
    send(*socket, reinterpret_cast<char *>(&cmd), sizeof(cmd), 0);

    // Initialises Response From The Server Variable
    char receiveBuffer[200] = "";
    // Gets Reponse From Server
    recv(*socket, receiveBuffer, 200, 0);
    // Checks Responses
    if (strcmp(receiveBuffer, "Login Failed") != 0) {
        // Throw Error To Show Login Failed
        throw ClientException("Login Creditinals Are Incorrect", 0001);
    }

    // Initialise User
    User user {};

    // Username is set to user
    user.SetUsername(username);

    // Returns User Pointer
    return &user;
}

User* User::Register(const SOCKET* socket) {
    // Initialise Variables
    char* username = nullptr;
    char* password = nullptr;
    std::vector<char*> body;

    // Sets input to username
    std::cout << "Username: " << std::endl;
    std::cin >> username;

    // Sets input to password
    std::cout << "Password: " << std::endl;
    std::cin >> password;

    // Pushes Parameters into Command Body
    body.push_back(username);
    body.push_back(password);

    // Constructs Command
    Command cmd = Command("Register", body);

    // Send Command To Server
    send(*socket, reinterpret_cast<char *>(&cmd), sizeof(cmd), 0);

    // Initialises Server Response Buffer
    char receiveBuffer[200] = "";

    // Recieves Response From Server
    recv(*socket, receiveBuffer, 200, 0);

    // Checks Reponse From Server
    if (strcmp(receiveBuffer, "Register Failed") != 0) {
        // Throw Error To Show Registering Failed
        throw ClientException("Failed To Register", 0002);
    }

    // Initialising user
    User user {};

    // Sets users Username
    user.SetUsername(username);

    // Returns pointer of user
    return &user;
}

// Abstraction For Setting Username of User
void User::SetUsername(char* username) {
    this -> username = username;
}

