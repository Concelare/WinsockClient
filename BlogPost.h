//
// Created by Ben on 06/01/2024.
//

#ifndef BLOGPOST_H
#define BLOGPOST_H

// Uses Winsock Client
#include <winsock2.h>


class BlogPost {
public:
    void SendPost(SOCKET socket);
    void DisplayPost() const;
    // Static Member
    static void ReadPosts(SOCKET socket);

    // Abstraction/Encapsulation Functions
    void SetTitle(char* title);
    void SetDescription(char* description);
    void SetCreator(char* user);
private:
    // Abstraction/Encapsulation
    char* title = nullptr;
    char* description = nullptr;
    char* creator = nullptr;
};

#endif //BLOGPOST_H
