//
// Created by Ben on 05/01/2024.
//

#include "ClientException.h"

ClientException::ClientException(char* desc, const int co) {
    description = desc;
    code = co;
}


// Polymorphism Overide
const char* ClientException::what() const noexcept {
    return this->description;
}
