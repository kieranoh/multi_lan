#include <string.h>

/* 给定一个用户输入的字符串，去除字符串末尾的空格。字符串应在原地修改。 */
void trim_spaces(char* str) {
    if (str == NULL) {
        return;
    }
    
    int len = strlen(str);
    int i = len - 1;
    
    // 从字符串末尾向前遍历，找到第一个非空格字符
    while (i >= 0 && (str[i] == ' ' || str[i] == '\t' || str[i] == '\n' || str[i] == '\r')) {
        i--;
    }
    
    // 在第一个非空格字符后添加字符串结束符
    str[i + 1] = '\0';
}