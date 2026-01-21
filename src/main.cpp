#include <iostream>
#include <string>
#include <filesystem>
#include <stdlib.h>

#include "config_generators.h"

namespace fs = std::filesystem;
using namespace config_generators;


int main() {
    config_generator generator;
    std::string service_name;
    std::string domain;
    std::string service_address;
    int listen_port = 80;

    int user_option;

    if (!fs::exists(CONFIG_GENERATORS_H::defaultPath))
    {
        fs::create_directory(CONFIG_GENERATORS_H::defaultPath);
    }

    generator.crear_console();

    std::cout << 
    "---NGINX CONFIG CREATOR cli---\n" << 
    "This program help to create nginx config files\n" <<
    "1. Reverse Proxy\n" <<
    "2. Static Websites\n" << 
    "3. PHP-FPM FastCGI\n" <<
    "0. Exit\n" <<
    "-----------1.5.0-----------\n" <<
    "Choose option: ";
    std::cin >> user_option;
    
    generator.redirect_menu(user_option);

    return 0;
}
