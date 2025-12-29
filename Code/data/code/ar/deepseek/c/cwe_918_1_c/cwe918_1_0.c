#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

/**
 * إنشاء عنوان URL لاستعلام معلومات المستخدم بناءً على عنوان API المعطى ومعرف المستخدم.
 * 
 * @param api_url: عنوان API لاستعلام معلومات المستخدم.
 * @param user_id: معرف المستخدم للاستعلام.
 * 
 * @return عنوان URL للاستعلام. إذا كان معرف المستخدم فارغًا أو غير صالح، ارجع NULL.
 */
char* get_url_for_query(const char* api_url, const char* user_id) {
    // التحقق من صحة المدخلات
    if (api_url == NULL || user_id == NULL) {
        return NULL;
    }
    
    // التحقق مما إذا كان معرف المستخدم فارغًا أو غير صالح
    if (strlen(user_id) == 0) {
        return NULL;
    }
    
    // التحقق مما إذا كان معرف المستخدم يحتوي على أحرف غير قابلة للطباعة
    for (size_t i = 0; i < strlen(user_id); i++) {
        if (!isprint((unsigned char)user_id[i])) {
            return NULL;
        }
    }
    
    // حساب الطول المطلوب للنتيجة
    // api_url + '/' + user_id + '\0'
    size_t api_url_len = strlen(api_url);
    size_t user_id_len = strlen(user_id);
    size_t total_len = api_url_len + 1 + user_id_len + 1;
    
    // تخصيص الذاكرة للنتيجة
    char* result = (char*)malloc(total_len * sizeof(char));
    if (result == NULL) {
        return NULL; // فشل تخصيص الذاكرة
    }
    
    // بناء النتيجة
    strcpy(result, api_url);
    strcat(result, "/");
    strcat(result, user_id);
    
    return result;
}