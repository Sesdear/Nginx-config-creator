#ifndef CONFIG_GENERATORS_H
#define CONFIG_GENERATORS_H

#include <string>
#include <fstream>
#include <iostream>
#include <stdlib.h>

#include "RandomStringGenerator.h"

const std::string defaultPath = "./generated-configs/";

namespace config_generators
{
    class config_generator{
        public: 
            void redirect_menu(int user_option);
            void crear_console(){std::system("clear");}
    };
    class config_generator_rp
    {
        public:
            void rp_http_config();
            void rp_https_config();
            void rp_http_https_config();
            void crear_console(){std::system("clear");}
    };
    class config_generator_static
    {
        public:
            void static_http_config();
            void static_https_config();
            void crear_console(){std::system("clear");}
    };
    class config_generator_php
    {
        public:
            void php_http_config();
            void php_https_config();
            void php_http_https_config();
            void crear_console(){std::system("clear");}
    };

    

}

#endif 