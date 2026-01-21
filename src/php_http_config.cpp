#include "config_generators.h"

using namespace config_generators;

void config_generator_php::php_http_config() 
{
    config_generator_php::crear_console();

    std::string fastcgi_pass, service_name, domain;
    int listen_port = 80;
    std::string defaultDir = "/var/www/";

    std::cout << "\nEnter service_name: ";
    std::cin >> service_name;

    std::cout << "Enter domain: ";
    std::cin >> domain;


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

    std::string file_name = service_name + "_php_http_" + random_string + ".conf";
    std::ofstream Config;

    Config.open(defaultPath + file_name);

    Config << 
    "server {\n" <<
    "    listen 80;\n" <<
    "    server_name " << domain << ";\n" <<
    "    root /var/www/" << domain << ";\n" <<
    "    index index.php index.html;\n" <<
    "    location / {\n" <<
    "        try_files $uri $uri/ /index.php?$query_string;\n" <<
    "    }\n" <<
    "    location ~ \\.php$ {\n" <<
    "        fastcgi_pass 127.0.0.1:9000;\n" <<
    "        fastcgi_index index.php;\n" <<
    "        fastcgi_param SCRIPT_FILENAME $document_root$fastcgi_script_name;\n" <<
    "        include fastcgi_params;\n" <<
    "    }\n" <<
    "    location ~ /\\.(ht|svn|git) {\n" <<
    "        deny all;\n" <<
    "    }\n" <<
    "}\n";


    Config.close();

    std::cout <<  "Generate file: " << file_name << "\n";
    
}