# Nginx Config Creator
## Start
#### Easy Start
```Bash
sudo wget https://github.com/Sesdear/Nginx-config-creator/releases/download/1.6.0/NginxConfigCreator -O /usr/bin/NginxConfigCreator
sudo chmod +x /usr/bin/NginxConfigCreator
NginxConfigCreator
```
[RU Readme](README.ru.md)

Simple solution to create basic nginx configs faster.

## Features

- Anti slowloris attack configs
- Easier and faster create configs
- More config types for anything solutions

## Requirements

- Operating System: Linux / macOS / Windows
- CMake 3.16+, GCC 9+, unistd, stdlib

## Installation

### Quick Install (Recommended)

```bash
sudo wget https://github.com/Sesdear/Nginx-config-creator/releases/download/2.0.0/nginxcc -O /usr/bin/nginxcc
sudo chmod +x /usr/bin/nginxcc
```

### Build from Source

```bash
git clone https://github.com/Sesdear/Nginx-config-creator.git
cd Nginx-config-creator
mkdir build && cd build
cmake ..
make -j$(nproc)
```

## Usage

```bash
nginxcc --help
```

### Available Flags

#### Common Flags
| Command                      | Description                                                                             |
| ---------------------------- | --------------------------------------------------------------------------------------- |
| `nginxcc --help`   `-h`      | Show help                                                                               |
| `nginxcc --type`   `-t`      | Type of config                                                                 Required |
| `nginxcc --domain` `-d`      | Listen domain                                                                  Required |
| `nginxcc --address`  `-a`    | Local redirect address                                                         Required |
| `nginxcc --output` `-o`      | Path to save config (Default: `/etc/nginx/sites-available/{domain}_{type}`)    Optional |
| `nginxcc --symlink`     `-s` | Automatic create symlink to `/etc/nginx/sites-enabled/`                        Optional |

#### SSL Flags

| Command                         | Description                                                                                  |
| ------------------------------- | -------------------------------------------------------------------------------------------- |
| `nginxcc --ssl-chipers`         | SSL Chipers (Default: `ECDHE-ECDSA-AES128-GCM-SHA256:ECDHE-RSA-AES128-GCM-SHA256`)  Optional |
| `nginxcc --ssl-session-timeout` | SSL Session Timeout in minutes (Default: `10`)                                      Optional |
| `nginxcc --ssl-session-cache`   | SSL Session Cache in megabytes (Default: `10`)                                      Optional |

### Types
| Name     | Description                       |
| -------- | --------------------------------- |
| `rp_hhs` | Reverse proxy http redirect https |
| `rp_h`   | Reverse proxy http                |
| `rp_hs`  | Reverse proxy https               |

### Examples

**Example 1: Basic usage**

```bash
nginxcc -t rp_hhs -d example.com -a http://127.0.0.1:8080 -s
```

**Example 2: Advanced usage**

```bash
nginxcc -t rp_hhs -d example.com -a http://127.0.0.1:8080 -o ./output/ -s
```

## Important Notes

- Generated files are basic templates.
- Always review and test configurations before using in production.
- This tool does not replace understanding of the underlying technology.

## License

This project is licensed under the [Apache License](LICENSE)

## Author

**HLNikNiky**:
[GitHub](https://github.com/Sesdear)\
[Telegram Channel](https://t.me/hlniknikydevblog)\
[X](https://x.com/sergeyorekhoval)

## Contributing

Contributions are welcome!

1. Fork the repository
2. Create a new branch
3. Make your changes
4. Open a Pull Request

