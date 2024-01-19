//
// Created by Ben on 08/01/2024.
//

#include "Admin.h"

#include <iostream>

#include "ClientException.h"
#include "Command.h"
#include "User.h"

void Admin::DeletePost(SOCKET socket, User user, char* post_title) {

    if (strcmp(user.username, "admin") != 0) {
        throw ClientException("User is not admin", 201);
    }

    std::vector<char*> body;

    body.push_back(post_title);

     Command cmd = Command("DeleteBlog", body);

    std::cout << "Attempting Post Deletion" << std::endl;

    send(socket, reinterpret_cast<char *>(&cmd), sizeof(cmd), 0);

    bool response = false;
    recv(socket, reinterpret_cast<char *>(&response), sizeof(response), 0);

    if (!response) {
        throw ClientException("Deleting Post Failed", 202);
    }

    std::cout << "Successfully Deleted Post" << std::endl;

}
