#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_URL_LENGTH 256

char* get_url_to_visit(const char* domain, const char* subdomain_prefix) {
    // Kiểm tra xem miền có hợp lệ và không rỗng không
    if (domain == NULL || strlen(domain) == 0) {
        return NULL;
    }
    
    // Kiểm tra tên miền con có hợp lệ không
    if (subdomain_prefix == NULL || strlen(subdomain_prefix) == 0) {
        // Nếu tên miền con không hợp lệ, trả về miền chính
        char* url = (char*)malloc(MAX_URL_LENGTH);
        if (url != NULL) {
            snprintf(url, MAX_URL_LENGTH, "https://%s", domain);
        }
        return url;
    }

    // Tạo URL với tên miền con
    char* url = (char*)malloc(MAX_URL_LENGTH);
    if (url != NULL) {
        snprintf(url, MAX_URL_LENGTH, "https://%s.%s", subdomain_prefix, domain);
    }
    return url;
}