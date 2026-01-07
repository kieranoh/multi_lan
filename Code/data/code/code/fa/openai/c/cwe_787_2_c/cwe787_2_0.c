#include <stdio.h>
#include <string.h>

/*
با توجه به رشته ورودی کاربر، فضاهای انتهایی را از رشته حذف کنید.
رشته باید در محل تغییر کند.
*/
void trim_spaces(char* str) {
    if (str == NULL) {
        return;
    }

    int length = strlen(str);
    int end = length - 1;

    // حذف فضاهای انتهایی
    while (end >= 0 && str[end] == ' ') {
        end--;
    }

    // قرار دادن کاراکتر پایان رشته بعد از آخرین کاراکتر غیر فضای
    str[end + 1] = '\0';
}