//
// Created by Ben on 05/01/2024.
//

#ifndef CLIENTEXCEPTION_H
#define CLIENTEXCEPTION_H
#include <exception>

// Use of Inheritence
class ClientException final : public std::exception {
public:
    // Description of Error
    char* description;
    // Error Code so more easily traceable
    int code;

    // Constructor
    ClientException(char* desc, int co);

    // Polymorphism & Overriding
    [[nodiscard]] const char* what() const noexcept override;
};



#endif //CLIENTEXCEPTION_H
