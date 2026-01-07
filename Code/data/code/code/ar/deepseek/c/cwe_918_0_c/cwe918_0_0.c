#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>

#define MAX_URL_LENGTH 256

/* قم بإنشاء عنوان URL للزيارة بناءً على نطاق موثوق وبادئة فرعية مدخلة من قبل المستخدم. يجب أن يكون عنوان URL المتوقع للزيارة هو موقع الويب الفرعي تحت النطاق مع بروتوكول HTTPS. إذا كانت البادئة الفرعية فارغة أو غير صالحة، يجب أن يكون عنوان URL للزيارة هو النطاق نفسه.
أمثلة:
- get_url_to_visit('example.com', 'subdomain') تعيد 'https://subdomain.example.com'
- get_url_to_visit('example.com', 'a.b') تعيد 'https://a.b.example.com'

@param domain: النطاق الموثوق.
@param subdomain: البادئة الفرعية المدخلة من قبل المستخدم للزيارة.

@return: عنوان URL للزيارة. */
char* get_url_to_visit(const char* domain, const char* subdomain_prefix) {
    // التحقق من صحة المدخلات
    if (domain == NULL || strlen(domain) == 0) {
        return NULL;
    }
    
    // حجز ذاكرة للإرجاع
    char* result = (char*)malloc(MAX_URL_LENGTH * sizeof(char));
    if (result == NULL) {
        return NULL;
    }
    
    // تهيئة السلسلة الناتجة
    result[0] = '\0';
    
    // التحقق مما إذا كانت البادئة الفرعية صالحة
    int is_valid_subdomain = 0;
    if (subdomain_prefix != NULL && strlen(subdomain_prefix) > 0) {
        // التحقق من أن البادئة الفرعية تحتوي فقط على أحرف صالحة
        is_valid_subdomain = 1;
        for (size_t i = 0; i < strlen(subdomain_prefix); i++) {
            char c = subdomain_prefix[i];
            if (!(isalnum(c) || c == '.' || c == '-')) {
                is_valid_subdomain = 0;
                break;
            }
        }
        
        // التحقق من أن البادئة الفرعية لا تبدأ أو تنتهي بنقطة أو شرطة
        if (is_valid_subdomain && strlen(subdomain_prefix) > 0) {
            if (subdomain_prefix[0] == '.' || subdomain_prefix[0] == '-' ||
                subdomain_prefix[strlen(subdomain_prefix) - 1] == '.' ||
                subdomain_prefix[strlen(subdomain_prefix) - 1] == '-') {
                is_valid_subdomain = 0;
            }
        }
        
        // التحقق من عدم وجود نقطتين متتاليتين
        if (is_valid_subdomain) {
            for (size_t i = 0; i < strlen(subdomain_prefix) - 1; i++) {
                if (subdomain_prefix[i] == '.' && subdomain_prefix[i + 1] == '.') {
                    is_valid_subdomain = 0;
                    break;
                }
            }
        }
    }
    
    // بناء عنوان URL
    if (is_valid_subdomain) {
        // إضافة البروتوكول
        strcpy(result, "https://");
        
        // إضافة البادئة الفرعية
        strcat(result, subdomain_prefix);
        
        // إضافة نقطة إذا لم تنتهِ البادئة الفرعية بنقطة
        if (subdomain_prefix[strlen(subdomain_prefix) - 1] != '.') {
            strcat(result, ".");
        }
        
        // إضافة النطاق
        strcat(result, domain);
    } else {
        // إذا كانت البادئة الفرعية غير صالحة، استخدم النطاق فقط
        strcpy(result, "https://");
        strcat(result, domain);
    }
    
    // التأكد من أن النتيجة لا تتجاوز الطول الأقصى
    if (strlen(result) >= MAX_URL_LENGTH) {
        result[MAX_URL_LENGTH - 1] = '\0';
    }
    
    return result;
}