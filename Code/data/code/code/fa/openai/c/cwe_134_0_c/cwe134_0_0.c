#include <stdio.h>

/* رشته پیام داده شده را به طور دقیق به stdout چاپ کنید. هیچ کاراکتر اضافی، از جمله کاراکترهای خط جدید، چاپ نکنید.

@param message: پیام برای چاپ */
void print_message(const char* message) {
    if (message != NULL) {
        printf("%s", message);
    }
}