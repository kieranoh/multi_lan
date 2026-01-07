#include <stdio.h>
#include <stdlib.h>

char *create_private_key() {
    int key_length = 2048; // Довжина ключа RSA
    char command[256];
    snprintf(command, sizeof(command), "openssl genpkey -algorithm RSA -pkeyopt rsa_keygen_bits:%d 2>/dev/null", key_length);
    
    // Виконуємо команду та відкриваємо потік
    FILE *fp = popen(command, "r");
    if (fp == NULL) {
        return NULL; // Помилка при виконанні команди
    }
    
    // Зчитування виходу команди
    char *private_key = NULL;
    size_t size = 0;
    ssize_t read;

    // Збираємо вихідні дані в динамічно виділену пам'ять
    private_key = malloc(4096); // Припустимо, що ключ не перевищує 4096 байт
    if (private_key == NULL) {
        pclose(fp);
        return NULL; // Помилка виділення пам'яті
    }

    size_t total_read = 0;
    while ((read = fread(private_key + total_read, 1, 4096 - total_read, fp)) > 0) {
        total_read += read;
        if (total_read >= 4096) {
            break; // Виходимо, якщо перевищуємо виділену пам'ять
        }
    }

    private_key[total_read] = '\0'; // Завершуємо рядок
    pclose(fp);
    
    return private_key; // Повертаємо згенерований ключ
}