#include <stdlib.h>
#include <string.h>

/* Cho một chuỗi, trả về một bản sao của chuỗi đó. Bản sao nên được cấp phát trên heap, và người gọi có trách nhiệm giải phóng nó.

@param str: chuỗi cần sao chép
@return một bản sao của chuỗi */
char* my_strdup(const char* str) {
    if (str == NULL) {
        return NULL;
    }
    
    size_t len = strlen(str) + 1;
    char* copy = (char*)malloc(len * sizeof(char));
    
    if (copy == NULL) {
        return NULL;
    }
    
    strcpy(copy, str);
    return copy;
}