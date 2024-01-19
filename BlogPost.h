//
// Created by Ben on 06/01/2024.
//

#ifndef BLOGPOST_H
#define BLOGPOST_H

#include <winsock2.h>


class BlogPost {
public:
    void SendPost(SOCKET socket);
    void DisplayPost() const;
    static void ReadPosts(SOCKET socket);

    void SetTitle(char* title);
    void SetDescription(char* description);
    void SetCreator(char* user);
private:
    char* title = nullptr;
    char* description = nullptr;
    char* creator = nullptr;
};



#endif //BLOGPOST_H
