#include <stdio.h>
#include <string.h>
#include <stdlib.h>

char* get_target_for_redirect(const char* target, const char* domain) {
    // إعداد سلسلة النطاق مع بروتوكول https
    char https_domain[256];
    snprintf(https_domain, sizeof(https_domain), "https://%s", domain);
    
    // تحقق مما إذا كانت السلسلة المستهدفة تبدأ بالنطاق
    if (strstr(target, https_domain) == target) {
        // إذا كانت السلسلة المستهدفة ضمن النطاق، نعيد العنوان المستهدف كما هو
        return strdup(target);
    } else {
        // إذا لم يكن ضمن النطاق، نعيد عنوان URL للنطاق لإعادة التوجيه
        return strdup(https_domain);
    }
}