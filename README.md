# Nginx-config-creator
Program help to create basic nginx configs \
This cli program can help to create basic nginx configs

## Start
#### Easy Start
```Bash
sudo wget https://github.com/Sesdear/Nginx-config-creator/releases/download/1.5.0/NginxConfigCreator -O /usr/bin/NginxConfigCreator
sudo chmod +x /usr/bin/NginxConfigCreator
NginxConfigCreator
```
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

