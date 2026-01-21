#include <iostream>
#include <string>
#include <fstream>
#include "RandomStringGenerator.h"
#include <filesystem>

namespace fs = std::filesystem;


void create_rp_config(std::string service_name, std::string domain);
void create_static_config(std::string service_name, std::string domain);
void create_php_config(std::string service_name, std::string domain);
void create_https_static_config(std::string service_name, std::string domain);

std::string generateRandomString(size_t length);
std::string defaultPath = "./config/";

int main() {
    
    std::string service_name;
    std::string domain;
    std::string service_address;
    int listen_port = 80;

    int user_option;

    if (!fs::exists(defaultPath))
    {
        fs::create_directory(defaultPath);
    }

    std::cout << "---NGINX CONFIG CREATOR cli---" << std::endl;
    std::cout << "This program help to create nginx config files" << std::endl << std::endl;
    std::cout << "1. Generate Reverse Proxy config" << std::endl;
    std::cout << "2. Generate Static config" << std::endl;
    std::cout << "3. Generate HTTPS Static config" << std::endl;
    std::cout << "4. Generate PHP-FPM" << std::endl;
    std::cout << "0. Exit" << std::endl;
    std::cout << "------------------------------" << std::endl;
    std::cout << "Choose option: ";

    std::cin >> user_option;

    if (user_option == 0) {std::exit(0);}
    

    std::cout << "\nEnter service_name: ";
    std::cin >> service_name;

    std::cout << "Enter domain: ";
    std::cin >> domain;

    switch (user_option)
    {
    case 1: 
        create_rp_config(service_name, domain);
        break;
    case 2:
        create_static_config(service_name, domain);
        break;
    case 3:
        create_https_static_config(service_name, domain);
        break;
    case 4:
        create_php_config(service_name, domain);
        break;
    default:
        break;
    }


    return 0;
}

void create_rp_config(std::string service_name, std::string domain) 
{
    std::string service_address;
    int listen_port = 80;
    
    std::cout << "Enter service address (e.g. http://127.0.0.1:8080): ";
    std::cin >> service_address;

    std::string random_string;
    try {
        random_string = generateRandomString(5);
    } catch (const std::exception& e) {
        std::cerr << "random string generate error: " << e.what() << std::endl;
        random_string = "default";
    }

    std::string file_name = service_name + "_rp" + random_string + ".conf";
    std::ofstream Config;

    Config.open(defaultPath + file_name);

    Config << "server {" << std::endl;
    Config << "    listen " << listen_port << ";" << std::endl;
    Config << "    server_name " << domain << ";" << std::endl << std::endl;
    Config << "    location / {" << std::endl;
    Config << "        proxy_pass " << service_address << ";" << std::endl;
    Config << "        proxy_set_header Host $host;" << std::endl;
    Config << "        proxy_set_header X-Real-IP $remote_addr;" << std::endl;
    Config << "        proxy_set_header X-Forwarded-For $proxy_add_x_forwarded_for;" << std::endl;
    Config << "        proxy_set_header X-Forwarded-Proto $scheme;" << std::endl;
    Config << "    }" << std::endl;
    Config << "}" << std::endl;

    Config.close();

    std::cout << "Generate file: " << file_name << "\n";
    
}

void create_static_config(std::string service_name, std::string domain) 
{
    int listen_port = 80;
    const std::string rootDir = "/var/www/html";
    
    std::string random_string;
    try {
        random_string = generateRandomString(5);
    } catch (const std::exception& e) {
        std::cerr << "random string generate error: " << e.what() << std::endl;
        random_string = "default";
    }

    std::string file_name = service_name + "_static" + random_string + ".conf";
    std::ofstream Config;

    Config.open(defaultPath + file_name);

    Config << "server {" << std::endl;
    Config << "    listen " << listen_port << ";" << std::endl;
    Config << "    server_name " << domain << ";" << std::endl << std::endl;
    Config << "    root " << rootDir << ";" << std::endl;
    Config << "    index index.html index.htm;" << std::endl;
    Config << "    location / {" << std::endl;
    Config << "        try_files $uri $uri/ =404;" << std::endl;
    Config << "    }" << std::endl;
    Config << "    location ~* \\.(jpg|jpeg|png|gif|ico|css|js)$ {" << std::endl;
    Config << "        expires 30d;" << std::endl;
    Config << "        add_header Cache-Control \"public\";" << std::endl;
    Config << "    }" << std::endl;
    Config << "}" << std::endl;

    Config.close();

    std::cout <<  "Generate file: " << file_name << "\n";
    
}

void create_php_config(std::string service_name, std::string domain) 
{
    std::string fastcgi_pass;
    int listen_port = 80;
    std::string defaultDir = "/var/www/";

    defaultDir = defaultDir + domain;

    std::cout << "Enter fastcgi_pass (e.g. 127.0.0.1:9000): ";
    std::cin >> fastcgi_pass;

    std::string random_string;
    try {
        random_string = generateRandomString(5);
    } catch (const std::exception& e) {
        std::cerr << "random string generate error: " << e.what() << std::endl;
        random_string = "default";
    }

    std::string file_name = service_name + "_static" + random_string + ".conf";
    std::ofstream Config;

    Config.open(defaultPath + file_name);

    Config << "server {" << std::endl;
    Config << "    listen " << listen_port << ";" << std::endl;
    Config << "    server_name " << domain << ";" << std::endl;
    Config << "    root " << defaultDir << ";" << std::endl;
    Config << "    index index.php index.html;" << std::endl;
    Config << "    location / {" << std::endl;
    Config << "        try_files $uri $uri/ /index.php?$query_string;" << std::endl;
    Config << "    }" << std::endl;
    Config << "    location ~ \\.php$ {" << std::endl;
    Config << "        fastcgi_pass " << fastcgi_pass << ";" << std::endl;
    Config << "        fastcgi_index index.php;" << std::endl;
    Config << "        fastcgi_param SCRIPT_FILENAME $document_root$fastcgi_script_name;" << std::endl;
    Config << "        include fastcgi_params;" << std::endl;
    Config << "    }" << std::endl;
    Config << "    location ~ /\\.ht {" << std::endl;
    Config << "        deny all;" << std::endl;
    Config << "    }" << std::endl;
    Config << "}" << std::endl;

    Config.close();

    std::cout <<  "Generate file: " << file_name << "\n";
    
}

void create_https_static_config(std::string service_name, std::string domain)
{
    int listen_port = 80;
    std::string defaultDir = "/var/www/html";

    std::string random_string;
    try {
        random_string = generateRandomString(5);
    } catch (const std::exception& e) {
        std::cerr << "random string generate error: " << e.what() << std::endl;
        random_string = "default";
    }

    std::string file_name = service_name + "_static" + random_string + ".conf";
    std::ofstream Config;

    Config.open(defaultPath + file_name);

    Config << 
"server {\n" <<
"    listen 443 ssl http2;\n" <<
"    server_name " << domain << ";\n" <<
"    ssl_certificate /etc/ssl/certs/" << domain << ".crt;\n" <<
"    ssl_certificate_key /etc/ssl/private/" << domain << ".key;\n" <<
"    ssl_protocols TLSv1.2 TLSv1.3;\n" <<
"    ssl_ciphers ECDHE-RSA-AES256-GCM-SHA512:DHE-RSA-AES256-GCM-SHA512;\n" <<
"    ssl_prefer_server_ciphers off;\n" <<
"    root " << defaultDir << ";\n" <<
"    index index.html;\n" <<
"}";

    

    Config.close();

    std::cout <<  "Generate file: " << file_name << "\n";
}