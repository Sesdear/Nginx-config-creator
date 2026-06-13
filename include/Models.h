#ifndef MODELS_H
#define MODELS_H

#include <string>

struct config_model
{
    std::string domain;
    std::string service_address;
    std::string output_path;
    bool is_symlink = false;
    std::string ssl_protocols;
    std::string ssl_chipers;
    int ssl_session_cache;
    int ssl_session_timeout;
};

#endif