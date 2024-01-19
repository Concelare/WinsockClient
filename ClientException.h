//
// Created by Ben on 05/01/2024.
//

#ifndef CLIENTEXCEPTION_H
#define CLIENTEXCEPTION_H
#include <exception>

// Inheritence
class ClientException : public std::exception {
public:
    char* description;
    int code;

    // Constructor
    ClientException(char* desc, int co);

    // Polymorpish
    [[nodiscard]] const char* what() const noexcept override;
};



#endif //CLIENTEXCEPTION_H
