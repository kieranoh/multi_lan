#include <stdio.h>
#include <stdlib.h>

char* read_stdin_to_buffer(int buf_size) {
    char* buf = (char*)malloc(buf_size);
    if (buf == NULL) {
        return NULL; // تحقق من فشل تخصيص الذاكرة
    }

    if (fgets(buf, buf_size, stdin) == NULL) {
        free(buf); // تحرير الذاكرة في حالة الفشل
        return NULL;
    }

    return buf; // إرجاع المخزن المؤقت
}