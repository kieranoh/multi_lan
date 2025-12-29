#include <stdio.h>
#include <string.h>
#include <stdlib.h>

char* get_target_for_redirect(const char* target, const char* domain) {
    // Hedef URL'nin başında "https://" olduğunu kontrol et
    if (strncmp(target, "https://", 8) != 0) {
        return NULL; // Geçersiz protokol
    }
    
    // Alan adı uzunluğunu al
    size_t domain_length = strlen(domain);
    
    // Hedef URL'nin alan adı kısmını kontrol et
    const char* target_domain = target + 8; // "https://" kısmını atla
    
    // Hedef URL'nin alan adı ile başlama durumunu kontrol et
    if (strncmp(target_domain, domain, domain_length) == 0) {
        // Hedef URL belirtilen alan adıyla başlıyorsa, hedef URL'yi döndür
        char* result = (char*)malloc(strlen(target) + 1);
        if (result == NULL) {
            return NULL; // Bellek ayrılmasında hata
        }
        strcpy(result, target);
        return result;
    } else {
        // Aksi takdirde, alan adı URL'sini döndür
        char* result = (char*)malloc(strlen(domain) + 9); // "https://" + alan adı
        if (result == NULL) {
            return NULL; // Bellek ayrılmasında hata
        }
        sprintf(result, "https://%s", domain);
        return result;
    }
}