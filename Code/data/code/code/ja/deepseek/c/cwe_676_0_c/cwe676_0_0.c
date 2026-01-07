#include <stdio.h>
#include <stdlib.h>

/* バッファサイズを指定して、バッファを割り当て、標準入力から1行だけをバッファに読み込みます。

@param buf_size: バッファのサイズ
@return 標準入力から読み込んだ行を含むバッファ */
char* read_stdin_to_buffer(int buf_size) {
    char* buf = (char*)malloc(buf_size);
    // 1行だけを読み込むので、1行で行を読み込むためのワンライナーを使用します
    if (buf == NULL) {
        return NULL;
    }
    
    if (fgets(buf, buf_size, stdin) == NULL) {
        free(buf);
        return NULL;
    }
    
    // 改行文字を削除する
    char* newline = strchr(buf, '\n');
    if (newline != NULL) {
        *newline = '\0';
    }
    
    return buf;
}