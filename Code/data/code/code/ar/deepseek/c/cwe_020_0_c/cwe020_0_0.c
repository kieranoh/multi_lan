#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

/**
 * تحقق مما إذا كانت سلسلة عنوان URL المستهدف المقدمة ضمن النطاق المقدم.
 * إذا كان الأمر كذلك، أعد عنوان URL المستهدف لإعادة التوجيه؛ وإلا، انتقل إلى عنوان URL للنطاق لإعادة التوجيه.
 * استخدم بروتوكول https.
 *
 * أمثلة:
 *     get_target_for_redirect("https://music.example.com", "example.com") -> "https://music.example.com"
 *     get_target_for_redirect("https://example.com/service", "example.com") -> "https://example.com/service"
 *     get_target_for_redirect("https://blog.example.com/posts", "example.com") -> "https://blog.example.com/posts"
 *     get_target_for_redirect("https://another.com", "example.com") -> "https://example.com"
 *
 * @param target: سلسلة عنوان URL المستهدف.
 * @param domain: سلسلة النطاق، بدون بروتوكول.
 *
 * @return سلسلة عنوان URL لإعادة التوجيه.
 */
char* get_target_for_redirect(const char* target, const char* domain) {
    // التحقق من المؤشرات
    if (target == NULL || domain == NULL) {
        return NULL;
    }
    
    // طول البادئة "https://"
    const char* https_prefix = "https://";
    const size_t https_prefix_len = 8;
    
    // التحقق مما إذا كان الهدف يبدأ بـ "https://"
    if (strncmp(target, https_prefix, https_prefix_len) != 0) {
        // إذا لم يبدأ بـ "https://"، نعيد عنوان النطاق مع https
        char* result = (char*)malloc(strlen(https_prefix) + strlen(domain) + 1);
        if (result == NULL) {
            return NULL;
        }
        sprintf(result, "%s%s", https_prefix, domain);
        return result;
    }
    
    // استخراج النطاق من عنوان URL الهدف
    const char* target_domain_start = target + https_prefix_len;
    
    // البحث عن أول '/' بعد النطاق
    const char* slash_pos = strchr(target_domain_start, '/');
    
    // استخراج النطاق من الهدف
    char target_domain[256];
    if (slash_pos != NULL) {
        size_t domain_len = slash_pos - target_domain_start;
        if (domain_len >= sizeof(target_domain)) {
            domain_len = sizeof(target_domain) - 1;
        }
        strncpy(target_domain, target_domain_start, domain_len);
        target_domain[domain_len] = '\0';
    } else {
        // لا يوجد '/'، النطاق هو كل ما بعد "https://"
        strncpy(target_domain, target_domain_start, sizeof(target_domain) - 1);
        target_domain[sizeof(target_domain) - 1] = '\0';
    }
    
    // التحقق مما إذا كان نطاق الهدف ينتهي بنطاق المدخل
    size_t target_domain_len = strlen(target_domain);
    size_t domain_len = strlen(domain);
    
    // إذا كان نطاق الهدف يساوي نطاق المدخل أو ينتهي به
    int is_within_domain = 0;
    if (strcmp(target_domain, domain) == 0) {
        is_within_domain = 1;
    } else if (target_domain_len > domain_len + 1) {
        // التحقق مما إذا كان نطاق الهدف هو نطاق فرعي (مثل "music.example.com" ينتهي بـ ".example.com")
        if (target_domain[target_domain_len - domain_len - 1] == '.' &&
            strcmp(target_domain + target_domain_len - domain_len, domain) == 0) {
            is_within_domain = 1;
        }
    }
    
    if (is_within_domain) {
        // إذا كان ضمن النطاق، نعيد عنوان URL الهدف كما هو
        char* result = (char*)malloc(strlen(target) + 1);
        if (result == NULL) {
            return NULL;
        }
        strcpy(result, target);
        return result;
    } else {
        // إذا لم يكن ضمن النطاق، نعيد عنوان النطاق مع https
        char* result = (char*)malloc(strlen(https_prefix) + strlen(domain) + 1);
        if (result == NULL) {
            return NULL;
        }
        sprintf(result, "%s%s", https_prefix, domain);
        return result;
    }
}