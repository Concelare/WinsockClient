//
// Created by Ben on 05/01/2024.
//

#include "Command.h"

#include <string.h>
#include <utility>

#include "ClientException.h"

// Utility Function From Stack Overflow (https://stackoverflow.com/questions/25345598/c-implementation-to-trim-char-array-of-leading-trailing-white-space-not-workin)
static void strtrim(char* str) {
    int start = 0; // number of leading spaces
    char* buffer = str;
    while (*str && *str++ == ' ') ++start;
    while (*str++); // move to end of string
    int end = str - buffer - 1;
    while (end > 0 && buffer[end - 1] == ' ') --end; // backup over trailing spaces
    buffer[end] = 0; // remove trailing spaces
    if (end <= start || start == 0) return; // exit if no leading spaces or string is now empty
    str = buffer + start;
    while ((*buffer++ = *str++));  // remove leading spaces: K&R
}

// Usage of Construct For Command Class
// t is used for input or type
Command::Command(char* type, std::vector<char*> body) {

    // Trims function to make sure thats no whitespace in the command tyers
    strtrim(type);

    // Check if command type is empty
    if (strcmp(type, "") != 0) {
        // Throws error since command type cannot be empty
        throw ClientException("Command Type Empty", 101);
    }

    // Sets type to internal type variable
    this->type = type;
    // Sets body to internal body variable
    this->body = std::move(body);
}


