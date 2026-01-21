#include "config_generators.h"

using namespace config_generators;

void config_generator_php::php_https_config() 
{
    config_generator_php::crear_console();

    std::string fastcgi_pass, service_name, domain;
    int listen_port = 80;
    std::string defaultDir = "/var/www/";
    

    std::cout << "\nEnter service_name: ";
    std::cin >> service_name;

    std::cout << "Enter domain: ";
    std::cin >> domain;

    std::cout << "Enter fastcgi_pass (e.g. 127.0.0.1:9000): ";
    std::cin >> fastcgi_pass;

    std::string random_string;
    try {
        random_string = generateRandomString(5);
    } catch (const std::exception& e) {
        std::cerr << "random string generate error: " << e.what() << std::endl;
        random_string = "default";
    }

    defaultDir = defaultDir + domain;

    std::string file_name = service_name + "_php_http_" + random_string + ".conf";
    std::ofstream Config;

    Config.open(defaultPath + file_name);

    Config <<
    "server {\n" <<
    "    listen 443 ssl http2;\n" <<
    "    server_name "<<domain<<";\n" <<
    "    ssl_certificate /etc/letsencrypt/live/"<<domain<<"/fullchain.pem;\n" <<
    "    ssl_certificate_key /etc/letsencrypt/live/"<<domain<<"/privkey.pem;\n" <<
    "    ssl_protocols TLSv1.2 TLSv1.3;\n" <<
    "    ssl_ciphers ECDHE-ECDSA-AES128-GCM-SHA256:ECDHE-RSA-AES128-GCM-SHA256;\n" <<
    "    ssl_prefer_server_ciphers off;\n" <<
    "    ssl_session_cache shared:SSL:10m;\n" <<
    "    ssl_session_timeout 10m;\n" <<
    "    root /var/www/"<<domain<<";\n" <<
    "    index index.php index.html;\n" <<
    "    location / {\n" <<
    "        try_files $uri $uri/ /index.php?$query_string;\n" <<
    "    }\n" <<
    "    location ~ \\.php$ {\n" <<
    "        fastcgi_pass "<<fastcgi_pass<<";\n" <<
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