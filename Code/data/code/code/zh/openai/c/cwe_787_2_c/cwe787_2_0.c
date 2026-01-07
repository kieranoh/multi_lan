#include <stdio.h>
#include <string.h>

/* 给定一个用户输入的字符串，去除字符串末尾的空格。字符串应在原地修改。 */
void trim_spaces(char* str) {
    if (str == NULL) {
        return; // 检查空指针
    }

    int len = strlen(str); // 获取字符串的长度
    int i;

    // 从字符串末尾开始寻找非空格字符
    for (i = len - 1; i >= 0; i--) {
        if (str[i] != ' ') {
            break; // 找到第一个非空格字符
        }
    }

    // 在找到的非空格字符后，添加字符串结束符
    str[i + 1] = '\0';
}