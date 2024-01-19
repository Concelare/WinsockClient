//
// Created by Ben on 08/01/2024.
//

#ifndef ADMIN_H
#define ADMIN_H

#include <winsock2.h>

#include "User.h"


class Admin {
public:
   // Static Member
   static void DeletePost(SOCKET socket,  User user, char* post_title);
};
#endif //ADMIN_H
