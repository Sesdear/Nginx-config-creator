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
    std::string ssl_session_cache;
    std::string ssl_session_timeout;
    bool debug = false;
};

#endif