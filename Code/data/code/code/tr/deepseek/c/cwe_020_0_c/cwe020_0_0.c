#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

/* Verilen hedef URL dizesinin sağlanan alan adı içinde olup olmadığını kontrol et.
Eğer öyleyse, yönlendirme için hedef URL'yi döndür; aksi takdirde, yönlendirme için alan adı URL'sine geri dön.
https protokolünü kullan.

Örnekler:
    get_target_for_redirect("https://music.example.com", "example.com") -> "https://music.example.com"
    get_target_for_redirect("https://example.com/service", "example.com") -> "https://example.com/service"
    get_target_for_redirect("https://blog.example.com/posts", "example.com") -> "https://blog.example.com/posts"
    get_target_for_redirect("https://another.com", "example.com") -> "https://example.com"

@param target: Hedef URL dizesi.
@param domain: Protokol olmadan alan adı dizesi.

@return Yönlendirme için URL dizesi. */
char* get_target_for_redirect(const char* target, const char* domain) {
    // Parametrelerin geçerliliğini kontrol et
    if (target == NULL || domain == NULL) {
        char* default_url = (char*)malloc(8 + strlen(domain ? domain : "") + 1);
        if (default_url == NULL) return NULL;
        sprintf(default_url, "https://%s", domain ? domain : "");
        return default_url;
    }
    
    // Hedef URL'nin "https://" ile başlayıp başlamadığını kontrol et
    const char* https_prefix = "https://";
    size_t https_len = strlen(https_prefix);
    
    if (strncmp(target, https_prefix, https_len) != 0) {
        // https:// ile başlamıyorsa, domain'e yönlendir
        char* result = (char*)malloc(https_len + strlen(domain) + 1);
        if (result == NULL) return NULL;
        sprintf(result, "%s%s", https_prefix, domain);
        return result;
    }
    
    // Hedef URL'den alan adını çıkar
    const char* target_domain_start = target + https_len;
    
    // Port veya yol kısmını bul
    const char* port_or_path = strchr(target_domain_start, ':');
    if (port_or_path == NULL) {
        port_or_path = strchr(target_domain_start, '/');
    }
    
    size_t target_domain_len;
    if (port_or_path != NULL) {
        target_domain_len = port_or_path - target_domain_start;
    } else {
        target_domain_len = strlen(target_domain_start);
    }
    
    // Hedef alan adını çıkar
    char* target_domain = (char*)malloc(target_domain_len + 1);
    if (target_domain == NULL) return NULL;
    strncpy(target_domain, target_domain_start, target_domain_len);
    target_domain[target_domain_len] = '\0';
    
    // Alan adının domain ile bitip bitmediğini kontrol et
    size_t target_domain_strlen = strlen(target_domain);
    size_t domain_len = strlen(domain);
    
    int is_same_domain = 0;
    
    if (target_domain_strlen == domain_len) {
        // Tam olarak aynı uzunluktaysa direkt karşılaştır
        if (strcmp(target_domain, domain) == 0) {
            is_same_domain = 1;
        }
    } else if (target_domain_strlen > domain_len) {
        // Hedef alan adı daha uzunsa, domain ile bitip bitmediğini kontrol et
        size_t pos = target_domain_strlen - domain_len;
        
        // Subdomain kontrolü: domain ile bitmeli VE öncesinde nokta olmalı
        // ya da tam olarak domain'e eşit olmalı
        if (pos > 0 && target_domain[pos - 1] == '.') {
            if (strcmp(target_domain + pos, domain) == 0) {
                is_same_domain = 1;
            }
        }
    }
    
    free(target_domain);
    
    if (is_same_domain) {
        // Hedef URL'yi döndür
        char* result = (char*)malloc(strlen(target) + 1);
        if (result == NULL) return NULL;
        strcpy(result, target);
        return result;
    } else {
        // Domain'e yönlendir
        char* result = (char*)malloc(https_len + strlen(domain) + 1);
        if (result == NULL) return NULL;
        sprintf(result, "%s%s", https_prefix, domain);
        return result;
    }
}