#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_URL_LENGTH 256

char* get_url_to_visit(const char* domain, const char* subdomain_prefix) {
    // تخصيص الذاكرة لعنوان URL
    char* url = (char*)malloc(MAX_URL_LENGTH);
    if (url == NULL) {
        return NULL; // في حالة حدوث خطأ في تخصيص الذاكرة
    }

    // التحقق مما إذا كانت البادئة الفرعية فارغة أو غير صالحة
    if (subdomain_prefix == NULL || strlen(subdomain_prefix) == 0) {
        snprintf(url, MAX_URL_LENGTH, "https://%s", domain);
    } else {
        // تشكيل عنوان URL مع البادئة الفرعية
        snprintf(url, MAX_URL_LENGTH, "https://%s.%s", subdomain_prefix, domain);
    }

    return url;
}