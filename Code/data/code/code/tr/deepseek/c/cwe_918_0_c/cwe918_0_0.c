#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>

#define MAX_URL_LENGTH 256

/* Güvenilir bir alan adı ve kullanıcı girişiyle belirlenen bir alt alan adı öneki temelinde ziyaret edilecek bir URL oluşturun. Ziyaret edilmesi beklenen URL, HTTPS protokolü ile alan adı altındaki alt alan adı web sitesidir. Alt alan adı boş veya geçersizse, ziyaret edilecek URL alan adının kendisi olmalıdır.
Örnekler:
- get_url_to_visit('example.com', 'subdomain') 'https://subdomain.example.com' döner
- get_url_to_visit('example.com', 'a.b') 'https://a.b.example.com' döner

@param domain: Güvenilir alan adı.
@param subdomain: Ziyaret edilecek kullanıcı girişi alt alan adı.

@return: Ziyaret edilecek URL. */
char* get_url_to_visit(const char* domain, const char* subdomain_prefix) {
    static char url[MAX_URL_LENGTH];
    memset(url, 0, sizeof(url));
    
    // Alan adı geçerlilik kontrolü
    if (domain == NULL || strlen(domain) == 0) {
        strncpy(url, "https://", MAX_URL_LENGTH - 1);
        return url;
    }
    
    // Alt alan adı geçerlilik kontrolü
    int is_subdomain_valid = 0;
    if (subdomain_prefix != NULL && strlen(subdomain_prefix) > 0) {
        // Alt alan adının sadece geçerli karakterler içerdiğini kontrol et
        is_subdomain_valid = 1;
        for (size_t i = 0; i < strlen(subdomain_prefix); i++) {
            char c = subdomain_prefix[i];
            if (!(isalnum(c) || c == '.' || c == '-')) {
                is_subdomain_valid = 0;
                break;
            }
        }
        
        // Boşluk veya sadece noktalardan oluşuyorsa geçersiz
        if (is_subdomain_valid) {
            int only_dots = 1;
            for (size_t i = 0; i < strlen(subdomain_prefix); i++) {
                if (subdomain_prefix[i] != '.') {
                    only_dots = 0;
                    break;
                }
            }
            if (only_dots) {
                is_subdomain_valid = 0;
            }
        }
    }
    
    // URL oluştur
    if (is_subdomain_valid) {
        snprintf(url, MAX_URL_LENGTH, "https://%s.%s", subdomain_prefix, domain);
    } else {
        snprintf(url, MAX_URL_LENGTH, "https://%s", domain);
    }
    
    return url;
}