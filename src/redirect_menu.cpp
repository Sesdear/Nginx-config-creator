#include <iostream>
#include <string>

#include <stdlib.h>

#include "config_generators.h"

using namespace config_generators;


void config_generator::redirect_menu(int user_option) {\
    config_generator_rp rp_generator;
    config_generator_static static_generator;
    config_generator_php php_generator;
    config_generator generator;
    int user_menu_option;

    generator.crear_console();

    switch (user_option)
    {
    case 0:
        std::exit(0);
    case 1: 
        std::cout <<
        "---NGINX CONFIG CREATOR cli---\n" << 
        "------------------------------\n" <<
        "Main Menu > Reverse Proxy\n" <<
        "------------------------------\n" <<
        "1. HTTP only\n" <<
        "2. HTTPS only\n" << 
        "3. HTTP redirect HTTPS\n" <<
        "0. Exit\n" <<
        "-----------1.5.0-----------\n" <<
        "Choose option: ";
        std::cin >> user_menu_option;

        switch (user_menu_option)
        {
        case 0:
            std::exit(0);
        case 1:
            rp_generator.rp_http_config();
            break;
        case 2:
            rp_generator.rp_https_config();
            break;
        case 3:
            rp_generator.rp_http_https_config();
            break;
        default:
            break;
        }
        break;
    case 2:
        std::cout <<
        "---NGINX CONFIG CREATOR cli---\n" << 
        "------------------------------\n" <<
        "Main Menu > Static Websites\n" <<
        "------------------------------\n" <<
        "1. HTTP only\n" <<
        "2. HTTP redirect HTTPS\n" <<
        "0. Exit\n" <<
        "-----------1.5.0-----------\n" <<
        "Choose option: ";
        std::cin >> user_menu_option;
        
        switch (user_menu_option)
        {
        case 0:
            std::exit(0);
        case 1:
            static_generator.static_http_config();
            break;
        case 2:
            static_generator.static_https_config();
            break;
        default:
            break;
        }
        break;
    case 3:
        std::cout <<
        "---NGINX CONFIG CREATOR cli---\n" << 
        "------------------------------\n" <<
        "Main Menu > PHP-FPM FastCGI\n" <<
        "------------------------------\n" <<
        "1. HTTP only\n" <<
        "2. HTTP redirect HTTPS\n" <<
        "0. Exit\n" <<
        "-----------1.5.0-----------\n" <<
        "Choose option: ";
        std::cin >> user_menu_option;
        
        switch (user_menu_option)
        {
        case 0:
            std::exit(0);
        case 1:
            php_generator.php_http_config();
            break;
        case 2:
            php_generator.php_https_config();
            break;
        default:
            break;
        }
        break;
    default:
        break;
    }
}
