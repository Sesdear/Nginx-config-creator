#include "config_generators.h"

using namespace config_generators;

void config_generator_static::static_http_config() 
{
    config_generator_static::crear_console();

    std::string random_string, service_name, domain;
    int listen_port = 80;
    const std::string rootDir = "/var/www/html";
    
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

    std::string file_name = service_name + "_static_http_" + random_string + ".conf";
    std::ofstream Config;

    Config.open(defaultPath + file_name);

    Config << 
    "server {\n" <<
    "    listen 80;\n" <<
    "    server_name " << domain << ";\n" <<
    "    root /var/www/"<<domain<<";\n" <<
    "    index index.html index.htm;\n" <<
    "    \n" <<
    "    location / {\n" <<
    "        try_files $uri $uri/ =404;\n" <<
    "        expires 1y;\n" <<
    "        add_header Cache-Control \"public, immutable\";\n" <<
    "    }\n" <<
    "    \n" <<
    "    location ~* \\.(jpg|jpeg|png|gif|ico|css|js|svg|woff|woff2|ttf|eot)$ {\n" <<
    "        expires 1y;\n" <<
    "        add_header Cache-Control \"public, immutable\";\n" <<
    "        access_log off;\n" <<
    "    }\n" <<
    "    \n" <<
    "    gzip on;\n" <<
    "    gzip_vary on;\n" <<
    "    gzip_min_length 1024;\n" <<
    "    gzip_types text/plain text/css text/xml text/javascript application/javascript application/xml+rss application/json;\n" <<
    "}\n";


    Config.close();

    std::cout <<  "Generate file: " << file_name << "\n";
    
}