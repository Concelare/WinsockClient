//
// Created by Ben on 08/01/2024.
//

#include "Admin.h"

#include <iostream>

#include "ClientException.h"
#include "Command.h"
#include "User.h"

void Admin::DeletePost(SOCKET socket, User user, char* post_title) {
    // Checks if username is admin if not throws error
    if (strcmp(user.username, "admin") != 0) {
        throw ClientException("User is not admin", 201);
    }

    // Initialise the body variable
    std::vector<char*> body;

    // Add post title to body
    body.push_back(post_title);

    // Constructs Command
    Command cmd = Command("DeleteBlog", body);

    std::cout << "Attempting Post Deletion" << std::endl;

    // Send Command To Server
    send(socket, reinterpret_cast<char *>(&cmd), sizeof(cmd), 0);
    // Initialised Boolean Response Variable
    bool response = false;

    // Recieve Boolean Response From Server
    recv(socket, reinterpret_cast<char *>(&response), sizeof(response), 0);

    // Check if Reponse is True
    if (!response) {
        // If the response is false post deletion failed so throw error
        throw ClientException("Deleting Post Failed", 202);
    }

    std::cout << "Successfully Deleted Post" << std::endl;

}
