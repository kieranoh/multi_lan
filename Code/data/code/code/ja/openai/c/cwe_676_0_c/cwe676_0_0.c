#include <stdio.h>
#include <stdlib.h>

char* read_stdin_to_buffer(int buf_size) {
    char* buf = (char*)malloc(buf_size);
    if (buf == NULL) {
        return NULL; // メモリ割り当て失敗時はNULLを返す
    }
    if (fgets(buf, buf_size, stdin) == NULL) {
        free(buf); // 読み込み失敗時はメモリを解放
        return NULL;
    }
    return buf; // 成功時はバッファを返す
}