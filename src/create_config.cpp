#include <fstream>
#include <iostream>
#include <stdlib.h>

#include "Models.h"
#include "Create_Configs.h"
#include "Helper.h"

bool create_rp_hhs(MODELS_H::config_model config_model)
{
    const char *c = config_model.output_path.c_str();

    if (!HELPER_H::check_directory_exists(c))
    {
        return false;
    }

    std::ofstream Config(config_model.output_path);

    Config << "server {\n"
           << "    listen " << 80 << ";\n"
           << "    server_name " << config_model.domain << ";\n"
           << "    return 301 https://$server_name$request_uri;\n"
           << "}\n"
           << "server {\n"
           << "    listen " << 443 << " ssl http2;\n"
           << "    server_name " << config_model.domain << ";\n"
           << "    ssl_certificate /etc/letsencrypt/live/" << config_model.domain << "/fullchain.pem;\n"
           << "    ssl_certificate_key /etc/letsencrypt/live/" << config_model.domain << "/privkey.pem;\n"
           << "    ssl_protocols " << config_model.ssl_protocols << ";\n"
           << "    ssl_ciphers " << config_model.ssl_chipers << ";\n"
           << "    ssl_prefer_server_ciphers off;\n"
           << "    ssl_session_cache shared:SSL:" << config_model.ssl_session_cache << "m;\n"
           << "    ssl_session_timeout " << config_model.ssl_session_timeout << "m;\n"
           << "    location / {\n"
           << "        proxy_pass " << config_model.service_address << ";\n"
           << "        proxy_set_header Host $host;\n"
           << "        proxy_set_header X-Real-IP $remote_addr;\n"
           << "        proxy_set_header X-Forwarded-For $proxy_add_x_forwarded_for;\n"
           << "        proxy_set_header X-Forwarded-Proto $scheme;\n"
           << "    }\n"
           << "}\n";
    Config.close();

    return true;
}