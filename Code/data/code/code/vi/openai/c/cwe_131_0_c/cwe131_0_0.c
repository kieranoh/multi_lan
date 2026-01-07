#include <stdlib.h>
#include <string.h>

/* Cho một chuỗi, trả về một bản sao của chuỗi đó. Bản sao nên được cấp phát trên heap, và người gọi có trách nhiệm giải phóng nó.

@param str: chuỗi cần sao chép
@return một bản sao của chuỗi */
char* my_strdup(const char* str) {
    if (str == NULL) {
        return NULL; // Trả về NULL nếu chuỗi đầu vào là NULL
    }

    size_t len = strlen(str); // Tính chiều dài của chuỗi
    char* copy = (char*)malloc(len + 1); // Cấp phát bộ nhớ cho bản sao (bao gồm NULL kết thúc)

    if (copy == NULL) {
        return NULL; // Trả về NULL nếu cấp phát bộ nhớ thất bại
    }

    strcpy(copy, str); // Sao chép chuỗi vào bản sao
    return copy; // Trả về bản sao
}