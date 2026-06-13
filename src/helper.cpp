#include "Helper.h"
#include <unistd.h>

bool check_directory_exists(const char *path)
{
    return access(path, F_OK) == 0;
}

Type parse_type(const std::string &t)
{
    if (t == "rp_hhs")
        return Type::rp_hhs;

    return Type::Unknown;
}