#include <fstream>
#include <iostream>
#include <stdlib.h>
#include <filesystem>

namespace fs = std::filesystem;

#include "Models.h"
#include "Create_Configs.h"
#include "Helper.h"

bool create_rp_hhs(MODELS_H::config_model config_model)
{
    if (config_model.debug)
    {
        std::cout << "[INFO]: Start create_rp_hhs function.\n";
    }

    if (!HELPER_H::check_directory_exists(config_model))
    {
        return false;
    }

    if (config_model.debug)
    {
        std::cout << "[INFO]: Directory check success.\n";
    }
    try
    {
        if (config_model.debug)
        {
            std::cout << "[INFO]: Attempting to open: " << config_model.output_path << std::endl;

            fs::path p = config_model.output_path;

            if (fs::exists(p))
            {
                std::cout << "[INFO]: File exists. Size: " << fs::file_size(p) << " bytes" << std::endl;

                auto perm = fs::status(p).permissions();
                std::cout << "[INFO]: Permissions (oct): "
                          << std::oct << static_cast<unsigned>(perm) << std::dec << std::endl;
            }
            else
            {
                std::cout << "[INFO]: File does not exist yet." << std::endl;
            }
        }

        std::ofstream Config(config_model.output_path, std::ios::out | std::ios::trunc);
        Config.exceptions(std::ios::failbit | std::ios::badbit);

        Config << "server {\n"
               << "    listen 80;\n"
               << "    server_name " << config_model.domain << ";\n"
               << "    return 301 https://$server_name$request_uri;\n"
               << "}\n";

        Config << "server {\n"
               << "    listen 443 ssl http2;\n"
               << "    server_name " << config_model.domain << ";\n"
               << "    ssl_certificate /etc/letsencrypt/live/" << config_model.domain << "/fullchain.pem;\n"
               << "    ssl_certificate_key /etc/letsencrypt/live/" << config_model.domain << "/privkey.pem;\n"
               << "    ssl_protocols " << config_model.ssl_protocols << ";\n"
               << "    ssl_ciphers " << config_model.ssl_chipers << ";\n"
               << "    ssl_prefer_server_ciphers off;\n";

        Config << "    ssl_session_cache shared:SSL:" << config_model.ssl_session_cache << "m;\n"
               << "    ssl_session_timeout " << config_model.ssl_session_timeout << "m;\n";

        Config << "    location / {\n"
               << "        proxy_pass " << config_model.service_address << ";\n"
               << "        proxy_set_header Host $host;\n"
               << "        proxy_set_header X-Real-IP $remote_addr;\n"
               << "        proxy_set_header X-Forwarded-For $proxy_add_x_forwarded_for;\n"
               << "        proxy_set_header X-Forwarded-Proto $scheme;\n"
               << "    }\n"
               << "}\n";

        Config.close();

        if (config_model.debug)
        {
            std::cout << "[INFO]: End of write file.\n";
        }
    }
    catch (const std::ios_base::failure &e)
    {
        std::cerr << "[ERROR]: Configuration file error: " << e.what() << "\n";
        std::cerr << "[ERROR]: Error code: " << e.code() << "\n";

        return false;
    }
    if (config_model.is_symlink)
    {
        HELPER_H::create_symlink(config_model);
    }

    if (config_model.debug)
    {
        std::cout << "[INFO]: create_rp_hhs success.\n";
    }
    return true;
}
