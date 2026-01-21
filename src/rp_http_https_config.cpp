#include "config_generators.h"

using namespace config_generators;

void config_generator_rp::rp_http_https_config() 
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

    std::string file_name = service_name + "_rp_http_https_" + random_string + ".conf";
    std::ofstream Config;

    Config.open(defaultPath + file_name);

    Config << 
    "server {\n" <<
    "    listen 80;\n" <<
    "    server_name " << domain << ";\n" <<
    "    return 301 https://$server_name$request_uri;\n" <<
    "}\n" <<
    "server {\n" <<
    "    listen 443 ssl http2;" <<
    "    server_name " << domain << ";\n" <<
    "    ssl_certificate /etc/letsencrypt/live/"<<domain<<"/fullchain.pem;\n" <<
    "    ssl_certificate_key /etc/letsencrypt/live/"<<domain<<"/privkey.pem;\n" <<
    "    ssl_protocols TLSv1.2 TLSv1.3;\n" <<
    "    ssl_ciphers ECDHE-ECDSA-AES128-GCM-SHA256:ECDHE-RSA-AES128-GCM-SHA256;\n" <<
    "    ssl_prefer_server_ciphers off;\n" <<
    "    ssl_session_cache shared:SSL:10m;\n" <<
    "    ssl_session_timeout 10m;\n" <<
    "    location / {\n" <<
    "        proxy_pass "<<service_address<<";\n" <<
    "        proxy_set_header Host $host;\n" <<
    "        proxy_set_header X-Real-IP $remote_addr;\n" <<
    "        proxy_set_header X-Forwarded-For $proxy_add_x_forwarded_for;\n" <<
    "        proxy_set_header X-Forwarded-Proto $scheme;\n" <<
    "    }\n" <<
    "}\n";

    Config.close();

    std::cout << "Generate file: " << file_name << "\n";
    
}