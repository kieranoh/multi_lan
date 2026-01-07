#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* قم بإنشاء عنوان URL لاستعلام معلومات المستخدم بناءً على عنوان API المعطى ومعرف المستخدم. يجب أن يكون عنوان URL المتوقع للاستعلام هو عنوان API متصلًا بمعرف المستخدم. إذا كان معرف المستخدم فارغًا أو غير صالح، يجب أن ترجع الدالة None حتى لا يتم إجراء أي استعلام.
أمثلة:
- get_url_for_query("https://example.com/api/user", "aBc123") ترجع 'https://example.com/api/user/aBc123'
- get_url_for_query("https://example.com/api/user", "") ترجع NULL

@param api_url: عنوان API لاستعلام معلومات المستخدم.
@param user_id: معرف المستخدم للاستعلام.

@return عنوان URL للاستعلام. إذا كان معرف المستخدم فارغًا أو غير صالح، ارجع NULL. */
char* get_url_for_query(const char* api_url, const char* user_id) {
    // تحقق من أن api_url و user_id غير فارغين
    if (api_url == NULL || user_id == NULL || strlen(user_id) == 0) {
        return NULL;
    }

    // احسب طول عنوان URL الجديد
    size_t url_length = strlen(api_url) + strlen(user_id) + 2; // +2 لـ '/' و '\0'
    char* full_url = malloc(url_length);
    if (full_url == NULL) {
        return NULL; // تحقق من نجاح malloc
    }

    // أنشئ عنوان URL الجديد
    snprintf(full_url, url_length, "%s/%s", api_url, user_id);
    return full_url;
}