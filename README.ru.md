# Nginx Config Creator

Простое решение для быстрого создания базовых конфигураций Nginx.

## Возможности

* Готовые настройки для защиты от Slowloris-атак
* Быстрое и удобное создание конфигураций
* Несколько типов конфигураций для различных сценариев использования

## Требования

* Операционная система: Linux / macOS / Windows
* CMake 3.16+
* GCC 9+
* unistd
* stdlib

## Установка

### Быстрая установка (рекомендуется)

```bash
sudo wget https://github.com/Sesdear/Nginx-config-creator/releases/download/2.0.0/NginxConfigCreator -O /usr/bin/nginxcc
sudo chmod +x /usr/bin/nginxcc
```

### Сборка из исходного кода

```bash
git clone https://github.com/Sesdear/Nginx-config-creator.git
cd Nginx-config-creator
mkdir build && cd build
cmake ..
make -j$(nproc)
```

## Использование

```bash
nginxcc -h
```

### Доступные параметры

| Параметр                | Описание                                                                   |
| ----------------------- | -------------------------------------------------------------------------- |
| `nginxcc --help` `-h`   | Показать справку                                                           |
| `nginxcc --type` `-t`   | Тип конфигурации                                                           |
| `nginxcc --domain` `-d` | Доменное имя                                                               |
| `nginxcc --local` `-l`  | Адрес для проксирования или перенаправления                                |
| `nginxcc --path` `-p`   | Путь сохранения конфигурации (по умолчанию: `/etc/nginx/sites-available/`) |
| `nginxcc --output` `-o` | Имя выходного файла                                                        |
| `nginxcc --ln` `-s`     | Автоматически создать символическую ссылку в `/etc/nginx/sites-enabled/`   |

### Типы конфигураций

| Название | Описание                                |
| -------- | --------------------------------------- |
| `rp_hhs` | Reverse Proxy с HTTP → HTTPS редиректом |
| `rp_h`   | Reverse Proxy только по HTTP            |
| `rp_hs`  | Reverse Proxy только по HTTPS           |

## Примеры

### Пример 1: Базовое использование

```bash
nginxcc -t rp_hhs -d example.com -l http://127.0.0.1:8080 --ln
```

### Пример 2: Расширенное использование

```bash
nginxcc -t rp_hhs -d example.com -l http://127.0.0.1:8080 -o ./output/ --ln
```

## Важные замечания

* Сгенерированные файлы являются базовыми шаблонами.
* Перед использованием в продакшене рекомендуется проверить и протестировать конфигурацию.
* Утилита не заменяет понимание принципов работы Nginx и его настройки.

## Лицензия

Проект распространяется по лицензии Apache License.

## Автор

**HLNikNiky**

GitHub: https://github.com/Sesdear

Telegram-канал: https://t.me/hlniknikydevblog

X (Twitter): https://x.com/sergeyorekhoval

## Вклад в проект

Любые улучшения и исправления приветствуются.

1. Сделайте Fork репозитория.
2. Создайте новую ветку.
3. Внесите изменения.
4. Создайте Pull Request.
