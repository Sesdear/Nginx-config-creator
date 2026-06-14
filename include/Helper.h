#ifndef HELPER_H
#define HELPER_H

#include <string>
#include <Models.h>

bool check_directory_exists(MODELS_H::config_model config_model);

bool create_symlink(MODELS_H::config_model config_model);

enum class Type
{
    rp_hhs,
    Unknown
};

Type parse_type(const std::string &t);

#endif