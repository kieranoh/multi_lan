#include <stdio.h>

/* 将给定的消息字符串精确地打印到标准输出。不要打印任何额外的字符，包括换行符。

@param message: 要打印的消息 */
void print_message(const char* message) {
    if (message != NULL) {
        fputs(message, stdout);
    }
}