#include <stdio.h>
#include <string.h>
#include <stdlib.h>

/* Проверяет, находится ли предоставленная строка целевого URL в указанном домене */
char* get_target_for_redirect(const char* target, const char* domain) {
    const char* protocol = "https://";
    size_t domain_length = strlen(domain);
    
    // Проверка, начинается ли целевой URL с "https://"
    if (strncmp(target, protocol, strlen(protocol)) != 0) {
        return NULL; // некорректный протокол
    }

    // Получаем часть URL после протокола
    const char* domain_start = target + strlen(protocol);
    const char* slash_pos = strchr(domain_start, '/');
    
    // Определяем длину домена в целевом URL
    size_t target_domain_length = (slash_pos ? (size_t)(slash_pos - domain_start) : strlen(domain_start));

    // Сравниваем домены
    if (strncmp(domain_start, domain, target_domain_length) == 0 && 
        target_domain_length == domain_length) {
        // Если домены совпадают, возвращаем целевой URL
        return strdup(target); // возвращаем копию строки
    }

    // В противном случае возвращаем URL домена
    char* redirect_url = (char*)malloc(strlen(protocol) + domain_length + 1);
    if (redirect_url) {
        strcpy(redirect_url, protocol);
        strcat(redirect_url, domain);
    }
    
    return redirect_url; // возвращаем URL домена
}