#include <stdio.h>
#include <string.h>

void trim_spaces(char* str) {
    // التحقق مما إذا كانت السلسلة غير فارغة
    if (str == NULL) return;

    int len = strlen(str);
    int end = len - 1;

    // إزالة المسافات من نهاية السلسلة
    while (end >= 0 && (str[end] == ' ' || str[end] == '\t')) {
        end--;
    }

    // تعيين نهاية السلسلة الجديدة
    str[end + 1] = '\0';
}