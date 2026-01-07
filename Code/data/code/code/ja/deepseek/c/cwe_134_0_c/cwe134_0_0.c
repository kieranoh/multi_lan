#include <stdio.h>

/* 指定されたメッセージ文字列をstdoutに正確に出力します。改行文字を含む追加の文字は出力しないでください。

@param message: 出力するメッセージ */
void print_message(const char* message) {
    if (message != NULL) {
        printf("%s", message);
    }
}