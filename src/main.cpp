#include <iostream>
#include <string>
#include <filesystem>
#include <stdlib.h>

#include "argparse/argparse.hpp"
#include "Models.h"
#include "Create_Configs.h"
#include "Helper.h"

namespace fs = std::filesystem;

int main(int argc, char *argv[])
{
    argparse::ArgumentParser program("nginxcc");

    program.add_description("CLI Tool for faster and easiest create basic nginx config templates.");

    // Default Vars
    const std::string defaultOutputPath = "/etc/nginx/sites-available/";
    const std::string defaultSymlinkPath = "/etc/nginx/sites-enabled/";
    const std::string defaultSSLChipers = "ECDHE-ECDSA-AES128-GCM-SHA256:ECDHE-RSA-AES128-GCM-SHA256";
    const std::string defaultSSLProtocols = "TLSv1.2 TLSv1.3";
    const int defaultSSLSessionTimeout = 10;
    const int defaultSSLSessionCache = 10;

    // Dynamic Vars
    std::string domain;
    std::string service_address;
    HELPER_H::Type type;
    bool is_symlink;
    bool is_complete;

    // Structs
    MODELS_H::config_model config_model;

    // Common Flags
    program.add_argument("-t", "--type")
        .help("Type of config")
        .required();
    program.add_argument("-d", "--domain")
        .help("Listen domain")
        .required();
    program.add_argument("-a", "--address")
        .help("Local redirect address")
        .required();
    program.add_argument("-s", "--symlink")
        .help("Automatic create symlink to /etc/nginx/sites-enabled/")
        .flag();
    program.add_argument("-o", "--output")
        .help("Path to save config (Default: /etc/nginx/sites-available/{domain}_{type})")
        .default_value(defaultOutputPath);

    // SSL Flags
    program.add_argument("--ssl-chipers")
        .help("SSL Chipers (Default: ECDHE-ECDSA-AES128-GCM-SHA256:ECDHE-RSA-AES128-GCM-SHA256")
        .default_value(defaultSSLChipers);
    program.add_argument("--ssl-session-timeout")
        .help("SSL Session Timeout in minutes (Default: 10)")
        .default_value(defaultSSLSessionTimeout);
    program.add_argument("--ssl-session-cache")
        .help("SSL Session Cache in megabytes (Default: 10)")
        .default_value(defaultSSLSessionCache);

    try
    {
        program.parse_args(argc, argv);
    }
    catch (const std::exception &err)
    {
        std::cerr << err.what() << std::endl;
        std::cerr << program;
        std::exit(1);
    }

    config_model.domain = program.get<std::string>("-d");
    config_model.service_address = program.get<std::string>("-a");
    config_model.output_path = program.get<std::string>("-o");
    config_model.is_symlink = program.get<bool>("-s");
    config_model.ssl_chipers = program.get<std::string>("--ssl-chipers");
    config_model.ssl_session_timeout = program.get<int>("--ssl-session-timeout");
    config_model.ssl_session_cache = program.get<int>("--ssl-session-cache");

    type = HELPER_H::parse_type(program.get<std::string>("-t"));
    switch (type)
    {
    case HELPER_H::Type::rp_hhs:
        is_complete = CREATE_CONFIGS_H::create_rp_hhs(config_model);
        break;

    case HELPER_H::Type::Unknown:
        std::cout << "Unknown type.\n";
        return 1;

    default:
        break;
    }

    if (!is_complete)
    {
        return 1;
    }

    std::cout << "Config success created!\n";

    return 0;
}
