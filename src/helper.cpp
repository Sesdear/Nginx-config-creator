#include "Helper.h"
#include "Models.h"
#include <unistd.h>
#include <filesystem>
#include <iostream>

namespace fs = std::filesystem;

bool check_directory_exists(MODELS_H::config_model config_model)
{
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
            return true;
        }
        catch (const fs::filesystem_error &e)
        {
            std::cout << "[ERROR]: Directory not available: " << e.what() << "\n";
            return false;
        }
    }
    return true;
}

bool create_symlink(MODELS_H::config_model config_model)
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
        return true;
    }
    catch (const fs::filesystem_error &e)
    {
        std::cerr << "[ERROR]: Symlink creation failed: " << e.what() << "\n";
        return false;
    }
}

Type parse_type(const std::string &t)
{
    if (t == "rp_hhs")
        return Type::rp_hhs;

    return Type::Unknown;
}
