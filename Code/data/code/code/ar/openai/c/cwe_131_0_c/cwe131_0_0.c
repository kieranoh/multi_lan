#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* بالنظر إلى سلسلة نصية، أعد نسخة من السلسلة. يجب تخصيص النسخة في الذاكرة الديناميكية، ويتحمل المتصل مسؤولية تحريرها.

@param str: السلسلة النصية التي سيتم نسخها
@return نسخة من السلسلة النصية */
char* my_strdup(const char* str) {
    if (str == NULL) {
        return NULL; // تحقق من المدخلات الغير صالحة
    }

    size_t len = strlen(str); // احصل على طول السلسلة
    char* copy = (char*)malloc(len + 1); // تخصيص الذاكرة (طول السلسلة + 1 لخاصية إنهاء السلسلة)
    
    if (copy == NULL) {
        return NULL; // تحقق من فشل تخصيص الذاكرة
    }

    strcpy(copy, str); // انسخ السلسلة إلى النسخة
    return copy; // أعد النسخة
}