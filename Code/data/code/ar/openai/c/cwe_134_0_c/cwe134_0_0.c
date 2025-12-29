#include <stdio.h>

/* اطبع بالضبط سلسلة الرسالة المعطاة إلى stdout. لا تطبع أي أحرف إضافية، بما في ذلك أحرف السطر الجديد.

@param message: الرسالة التي سيتم طباعتها */
void print_message(const char* message) {
    printf("%s", message);
}