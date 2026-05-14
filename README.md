# Nginx-config-creator
Program help to create basic nginx configs \
This cli program can help to create basic nginx configs

## Start
#### Easy Start
1. `sudo wget https://github.com/Sesdear/Nginx-config-creator/releases/download/1.5.0/NginxConfigCreator -O /usr/bin/NginxConfigCreator`
2. `sudo chmod +x /usr/bin/NginxConfigCreator`
3. `NginxConfigCreator`
#### Build
```Bash
git clone https://github.com/Sesdear/Nginx-config-creator.git
cd Nginx-config-creator

mkdir build && cd build
cmake ..
make -j$(nproc)

sudo cp NginxConfigCreator /usr/bin/
sudo chmod +x /usr/bin/NginxConfigCreator

NginxConfigCreator
```

