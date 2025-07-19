#!/bin/bash

# Проверяем, установлен ли пакет libnotify-bin (для уведомлений)
if ! command -v notify-send &> /dev/null; then
    echo "Пакет libnotify-bin не установлен. Установите его командой:"
    echo "sudo apt install libnotify-bin"
    exit 1
fi

# Запрашиваем у пользователя количество минут
read -p "Введите количество минут для таймера: " minutes

# Проверяем, что введено число
if ! [[ "$minutes" =~ ^[0-9]+$ ]]; then
    echo "Ошибка: введите целое число минут."
    exit 1
fi

# Переводим минуты в секунды
seconds=$((minutes * 60))

echo "Таймер запущен на $minutes минут(ы)."

# Ожидаем указанное время
sleep "$seconds"

# Отправляем уведомление
notify-send "Таймер завершен" "Прошло $minutes минут(ы). Время закончилось!" -u critical

# Проигрываем звук (если установлен пакет sox)
if command -v play &> /dev/null; then
    play -n synth 0.5 sine 800 vol 0.5 2>/dev/null
fi

echo "Время вышло! $minutes минут(ы) прошло."
