#include <string.h>
#include <ctype.h>

/* بالنظر إلى سلسلة مدخلة من المستخدم، قم بإزالة المسافات الزائدة من نهاية السلسلة. يجب تعديل السلسلة في مكانها. */
void trim_spaces(char* str) {
    if (str == NULL) {
        return;
    }
    
    int len = strlen(str);
    int i = len - 1;
    
    // ابحث عن آخر حرف ليس مسافة بيضاء
    while (i >= 0 && isspace((unsigned char)str[i])) {
        i--;
    }
    
    // أضف حرف الإنهاء في الموضع المناسب
    str[i + 1] = '\0';
}