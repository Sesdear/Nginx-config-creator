#ifndef HELPER_H
#define HELPER_H

#include <string>

bool check_directory_exists(const char *path);

enum class Type
{
    rp_hhs,
    Unknown
};

Type parse_type(const std::string &t);

#endif