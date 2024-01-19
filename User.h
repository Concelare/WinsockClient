//
// Created by Benjamin Thompson on 02/01/2024.
//

#ifndef USER_H
#define USER_H

#include <winsock2.h>

class User final {
public:
    static User* login(const SOCKET* socket);
    static User* Register(const SOCKET* socket);
    void SetUsername(char* username);

    friend class Admin;
private:
    char* username;
};
#endif //USER_H
