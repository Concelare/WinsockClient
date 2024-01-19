//
// Created by Ben on 06/01/2024.
//

#include "BlogPost.h"

#include <iostream>

#include "ClientException.h"
#include "Command.h"

void BlogPost::SendPost(const SOCKET socket) {

    std::vector<char*> body;

    body.push_back(reinterpret_cast<char *>(this));

    Command cmd = Command("PostBlog", body);

    send(socket, reinterpret_cast<char *>(&cmd), sizeof(cmd), 0);

    bool response;

    recv(socket, reinterpret_cast<char *>(&response), sizeof(response), 0);

    if (!response) {
        throw ClientException("Failed to post blog", 301);
    }
}

void BlogPost::DisplayPost() const {
    std::cout << "Title: " << this->title << std::endl << "Creator: " << this->creator << std::endl << this->description << std::endl << std::endl;
}

void BlogPost::ReadPosts(const SOCKET socket) {
    const std::vector<char*> body;
    Command cmd = Command("ReadBlog", body);

    send(socket, reinterpret_cast<char *>(&cmd), sizeof(cmd), 0 );

    std::vector<BlogPost> response;

    recv(socket, reinterpret_cast<char *>(&response), sizeof(response), 0);

    for (BlogPost response1 : response) {
        response1.DisplayPost();
    }
}

void BlogPost::SetTitle(char* title) {
    this->title = title;
}

void BlogPost::SetDescription(char* description) {
    this->description = description;
}

void BlogPost::SetCreator(char* user) {
    this->creator = user;
}
