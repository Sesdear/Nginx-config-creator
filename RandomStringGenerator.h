#ifndef RANDOM_STRING_GENERATOR_H
#define RANDOM_STRING_GENERATOR_H

#include <string>
#include <random>
#include <algorithm>
std::string generateRandomString(size_t length) {
    const std::string CHARACTERS = "ABCDEFGHIJKLMNOPQRSTUVWXYZ"
                                    "abcdefghijklmnopqrstuvwxyz"
                                    "0123456789";
    
    std::random_device rd;
    std::mt19937 generator(rd());
    std::uniform_int_distribution<> distribution(0, static_cast<int>(CHARACTERS.size() - 1));

    std::string random_string;
    random_string.reserve(length);

    for (size_t i = 0; i < length; ++i) {
        random_string += CHARACTERS[distribution(generator)];
    }

    return random_string;
}

#endif // RANDOM_STRING_GENERATOR_H