#include <stdlib.h>
#include <string.h>

/* 给定一个字符串，返回该字符串的副本。副本应分配在堆上，调用者负责释放它。

@param str: 要复制的字符串
@return 字符串的副本 */
char* my_strdup(const char* str) {
    if (str == NULL) {
        return NULL; // 处理空指针的情况
    }

    size_t len = strlen(str); // 获取字符串长度
    char* copy = (char*)malloc(len + 1); // 分配内存 (+1 以包含空字符)
    
    if (copy == NULL) {
        return NULL; // 处理内存分配失败的情况
    }

    strcpy(copy, str); // 复制字符串
    return copy; // 返回副本
}