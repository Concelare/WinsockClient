//
// Created by Ben on 06/01/2024.
//

#include "BlogPost.h"

#include <iostream>

#include "ClientException.h"
#include "Command.h"

// Sends Post to Server
void BlogPost::SendPost(const SOCKET socket) {

    // Initialise Body
    std::vector<char*> body;

    // Add Post To The Command Body
    body.push_back(reinterpret_cast<char *>(this));

    // Construct The Command
    Command cmd = Command("PostBlog", body);

    // Send the Command to the server
    send(socket, reinterpret_cast<char *>(&cmd), sizeof(cmd), 0);

    // Response Variable Initialised
    bool response;

    // Recieve Response From Server
    recv(socket, reinterpret_cast<char *>(&response), sizeof(response), 0);

    // Check response to see if post successfully posted
    if (!response) {
        // Throw error to show post failed to send
        throw ClientException("Failed to post blog", 301);
    }
}

// Displays Post
void BlogPost::DisplayPost() const {
    std::cout << "Title: " << this->title << std::endl << "Creator: " << this->creator << std::endl << this->description << std::endl << std::endl;
}

// Retrieves & Displays Posts
void BlogPost::ReadPosts(const SOCKET socket) {
    // Initialise Const Variable
    const std::vector<char*> body;

    // Construct Command
    Command cmd = Command("ReadBlog", body);


    // Send Command To Server Using Winsock
    send(socket, reinterpret_cast<char *>(&cmd), sizeof(cmd), 0 );

    // Initialise Vector Response of Posts
    std::vector<BlogPost> posts;

    // Recieve Posts Response using Winsock
    recv(socket, reinterpret_cast<char *>(&posts), sizeof(posts), 0);

    // Loops Posts & Calls Display Posts
    for (BlogPost post : posts) {
        post.DisplayPost();
    }
}

// Abstraction: Sets The Title
void BlogPost::SetTitle(char* title) {
    this->title = title;
}

// Abstraction: Sets The Description
void BlogPost::SetDescription(char* description) {
    this->description = description;
}

// Abstraction: Sets The Creator
void BlogPost::SetCreator(char* user) {
    this->creator = user;
}
