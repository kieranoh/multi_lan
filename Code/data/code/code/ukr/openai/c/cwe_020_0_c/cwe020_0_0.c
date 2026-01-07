#include <stdio.h>
#include <string.h>
#include <stdlib.h>

char* get_target_for_redirect(const char* target, const char* domain) {
    // Перевірка, чи URL починається з https://
    if (strncmp(target, "https://", 8) != 0) {
        return NULL; // Повертаємо NULL, якщо протокол не https
    }

    // Формуємо домен з протоколом
    char domain_with_protocol[256];
    snprintf(domain_with_protocol, sizeof(domain_with_protocol), "https://%s", domain);

    // Перевіряємо, чи target починається з domain_with_protocol
    if (strncmp(target, domain_with_protocol, strlen(domain_with_protocol)) == 0) {
        // Якщо так, повертаємо оригінальний target
        return strdup(target);
    } else {
        // Інакше повертаємо домен з протоколом
        return strdup(domain_with_protocol);
    }
}