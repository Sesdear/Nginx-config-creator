#include "config_generators.h"

using namespace config_generators;

void config_generator_static::static_https_config() 
{
    config_generator_static::crear_console();

    int listen_port = 80;
    const std::string rootDir = "/var/www/html";
    std::string random_string, service_name, domain;

    std::cout << "\nEnter service_name: ";
    std::cin >> service_name;

    std::cout << "Enter domain: ";
    std::cin >> domain;

    try {
        random_string = generateRandomString(5);
    } catch (const std::exception& e) {
        std::cerr << "random string generate error: " << e.what() << std::endl;
        random_string = "default";
    }

    std::string file_name = service_name + "_static_https_" + random_string + ".conf";
    std::ofstream Config;

    Config.open(defaultPath + file_name);

    Config << 
    "server {\n" <<
    "    listen 80;\n" <<
    "    server_name " << domain << ";\n" <<
    "    return 301 https://$server_name$request_uri;\n" <<
    "}\n" <<
    "\n" <<
    "server {\n" <<
    "    listen 443 ssl http2;\n" <<
    "    server_name "<<domain<<";\n" <<
    "    \n" <<
    "    ssl_certificate /etc/letsencrypt/live/"<<domain<<"/fullchain.pem;\n" <<
    "    ssl_certificate_key /etc/letsencrypt/live/"<<domain<<"/privkey.pem;\n" <<
    "    \n" <<
    "    ssl_protocols TLSv1.2 TLSv1.3;\n" <<
    "    \n" <<
    "    root /var/www/"<<domain<<";\n" <<
    "    index index.html;\n" <<
    "    \n" <<
    "    location / {\n" <<
    "        try_files $uri $uri/ =404;\n" <<
    "        expires 1y;\n" <<
    "        add_header Cache-Control \"public, immutable\";\n" <<
    "    }\n" <<
    "}\n";



    Config.close();

    std::cout <<  "Generate file: " << file_name << "\n";
    
}