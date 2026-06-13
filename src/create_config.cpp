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

    fs::path file_path(config_model.output_path);
    fs::path parent_dir = file_path.parent_path();

    if (parent_dir.empty())
    {
        parent_dir = ".";
    }

    if (!fs::exists(parent_dir))
    {
        if (config_model.debug)
        {
            std::cout << "[INFO]: Directory " << parent_dir << " does not exist. Trying to create...\n";
        }

        try
        {
            fs::create_directories(parent_dir);
        }
        catch (const fs::filesystem_error &e)
        {
            std::cout << "[ERROR]: Directory not available: " << e.what() << "\n";
            return false;
        }
    }

    if (config_model.debug)
    {
        std::cout << "[INFO]: Directory check success.\n";
    }
    try
    {
        if (config_model.debug)
        {
            std::cout << "[INFO]: Start write file.\n";
        }
        std::ofstream Config;

        Config.exceptions(std::ios::failbit | std::ios::badbit);
        Config.open(config_model.output_path);

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
        try
        {
            fs::path target = config_model.output_path;

            fs::path enabled_dir = "/etc/nginx/sites-enabled/";

            fs::path link = enabled_dir / target.filename();

            if (config_model.debug)
            {
                std::cout << "[INFO]: Creating symlink from " << target << " to " << link << "\n";
            }

            if (fs::exists(link) || fs::is_symlink(link))
            {
                fs::remove(link);
            }

            fs::create_symlink(target, link);

            std::cout << "Symlink successfully created!\n";
        }
        catch (const fs::filesystem_error &e)
        {
            std::cerr << "[ERROR]: Symlink creation failed: " << e.what() << "\n";
        }
    }

    if (config_model.debug)
    {
        std::cout << "[INFO]: create_rp_hhs success.\n";
    }
    return true;
}
