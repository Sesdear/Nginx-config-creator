#include "config_generators.h"

using namespace config_generators;

void config_generator_rp::rp_http_config() 
{
    config_generator_rp::crear_console();

    std::string service_address, service_name, domain;
    int listen_port = 80;

    std::cout << "\nEnter service_name: ";
    std::cin >> service_name;

    std::cout << "Enter domain: ";
    std::cin >> domain;
    
    std::cout << "Enter service address (e.g. http://127.0.0.1:8080): ";
    std::cin >> service_address;

    std::string random_string;
    try {
        random_string = generateRandomString(5);
    } catch (const std::exception& e) {
        std::cerr << "random string generate error: " << e.what() << std::endl;
        random_string = "default";
    }

    std::string file_name = service_name + "_rp_http_" + random_string + ".conf";
    std::ofstream Config;

    Config.open(defaultPath + file_name);

    Config << 
    "server {\n" <<
    "    listen "<<listen_port<<";\n" << 
    "    server_name "<<domain<<";\n" << 
    "    location / {\n" << 
    "        proxy_pass "<<service_address<<";\n" << 
    "        proxy_set_header Host $host;\n" << 
    "        proxy_set_header X-Real-IP $remote_addr;\n" << 
    "        proxy_set_header X-Forwarded-For $proxy_add_x_forwarded_for;\n" << 
    "        proxy_set_header X-Forwarded-Proto $scheme;\n" << 
    "    }\n" <<
    "}";

    Config.close();

    std::cout << "Generate file: " << file_name << "\n";
    
}