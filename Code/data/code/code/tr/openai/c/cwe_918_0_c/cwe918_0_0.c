#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_URL_LENGTH 256

char* get_url_to_visit(const char* domain, const char* subdomain_prefix) {
    // URL'yi oluşturmak için bir tampon oluştur
    char* url = (char*)malloc(MAX_URL_LENGTH);
    if (url == NULL) {
        return NULL; // Bellek tahsisi başarısızsa NULL döner
    }

    // Alt alan adı geçerli değilse, sadece alan adını kullan
    if (subdomain_prefix == NULL || strlen(subdomain_prefix) == 0) {
        snprintf(url, MAX_URL_LENGTH, "https://%s", domain);
    } else {
        // Alt alan adı geçerliyse, tam URL'yi oluştur
        snprintf(url, MAX_URL_LENGTH, "https://%s.%s", subdomain_prefix, domain);
    }

    return url; // Oluşturulan URL döner
}