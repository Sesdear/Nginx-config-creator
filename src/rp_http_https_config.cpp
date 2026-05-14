#include "config_generators.h"
using namespace config_generators;

void config_generator_rp::rp_http_https_config()
{
    config_generator_rp::crear_console();

    std::string service_name, domain, service_address;
    std::string custom_path_str;
    bool isCustomPath = false;
    std::filesystem::path defaultPath = "/etc/nginx/sites-available/";

    std::cout << "\nEnter service_name: ";
    std::cin >> service_name;
    std::cout << "Enter domain: ";
    std::cin >> domain;
    std::cout << "Enter service address (e.g. http://127.0.0.1:8080): ";
    std::cin >> service_address;

    bool pathSelected = false;

    while (!pathSelected)
    {
        std::cout << "Save config to default nginx directory? (" << defaultPath << ")\nY/n: ";

        char yesOrNo{};
        std::cin >> yesOrNo;
        std::cin.ignore(1000, '\n');

        if (yesOrNo == 'y' || yesOrNo == 'Y')
        {
            isCustomPath = false;
            if (std::filesystem::is_directory(defaultPath))
            {
                std::cout << "Using default directory.\n";
                pathSelected = true;
            }
            else
            {
                std::cout << "Default nginx path does not exist!\n";
                isCustomPath = true;
            }
        }
        else if (yesOrNo == 'n' || yesOrNo == 'N')
        {
            isCustomPath = true;
        }
        else
        {
            std::cout << "Invalid input. Please enter Y or N.\n";
            continue;
        }

        if (isCustomPath)
        {
            while (true)
            {
                std::cout << "Enter path to save config: ";
                std::cin >> custom_path_str;
                std::cin.ignore(1000, '\n');

                std::filesystem::path p(custom_path_str);

                if (std::filesystem::is_directory(p))
                {
                    std::cout << "Custom path will be used.\n";
                    pathSelected = true;
                    break;
                }
                else
                {
                    std::cout << "Input path does not exist!\n";
                    char create{};
                    std::cout << "Create this directory? (Y/n): ";
                    std::cin >> create;
                    std::cin.ignore(1000, '\n');

                    if (create == 'y' || create == 'Y')
                    {
                        try
                        {
                            if (std::filesystem::create_directories(p))
                            {
                                std::cout << "Directory created successfully.\n";
                                pathSelected = true;
                                break;
                            }
                            else
                            {
                                std::cout << "Failed to create directory.\n";
                            }
                        }
                        catch (const std::filesystem::filesystem_error &e)
                        {
                            std::cout << "Error creating directory: " << e.what() << std::endl;
                        }
                    }
                }
            }
        }
    }

    std::string random_string = "default";
    try
    {
        random_string = generateRandomString(5);
    }
    catch (const std::exception &e)
    {
        std::cerr << "random string generate error: " << e.what() << std::endl;
    }

    std::string file_name = service_name + "_rp_http_https_" + random_string;

    std::ofstream Config;
    std::filesystem::path fullPath;

    if (isCustomPath)
        fullPath = std::filesystem::path(custom_path_str) / file_name;
    else
        fullPath = defaultPath / file_name;

    Config.open(fullPath);

    if (!Config.is_open())
    {
        std::cerr << "Error: Cannot open file for writing: " << fullPath << std::endl;
        std::cerr << "Try running with sudo if using default path.\n";
        return;
    }

    Config << "server {\n"
           << "    listen " << 80 << ";\n"
           << "    server_name " << domain << ";\n"
           << "    return 301 https://$server_name$request_uri;\n"
           << "}\n\n"
           << "server {\n"
           << "    listen " << 443 << " ssl http2;\n"
           << "    server_name " << domain << ";\n"
           << "    ssl_certificate /etc/letsencrypt/live/" << domain << "/fullchain.pem;\n"
           << "    ssl_certificate_key /etc/letsencrypt/live/" << domain << "/privkey.pem;\n"
           << "    ssl_protocols TLSv1.2 TLSv1.3;\n"
           << "    ssl_ciphers ECDHE-ECDSA-AES128-GCM-SHA256:ECDHE-RSA-AES128-GCM-SHA256;\n"
           << "    ssl_prefer_server_ciphers off;\n"
           << "    ssl_session_cache shared:SSL:10m;\n"
           << "    ssl_session_timeout 10m;\n"
           << "    location / {\n"
           << "        proxy_pass " << service_address << ";\n"
           << "        proxy_set_header Host $host;\n"
           << "        proxy_set_header X-Real-IP $remote_addr;\n"
           << "        proxy_set_header X-Forwarded-For $proxy_add_x_forwarded_for;\n"
           << "        proxy_set_header X-Forwarded-Proto $scheme;\n"
           << "    }\n"
           << "}\n";

    Config.close();
    std::cout << "Config successfully generated: " << fullPath << "\n";
}