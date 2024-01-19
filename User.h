//
// Created by Benjamin Thompson on 02/01/2024.
//

#ifndef USER_H
#define USER_H

#include <winsock2.h>

class User final {
public:
    // Static Members
    static User* login(const SOCKET* socket);
    static User* Register(const SOCKET* socket);
    void SetUsername(char* username);

    // Friendship for Admin Class
    friend class Admin;
private:
    // Encapulation & Inheritence
    char* username;
};
#endif //USER_H
