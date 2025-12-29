#include <stdlib.h>
#include <string.h>

/*
要求されたバッファサイズに基づいて、そのサイズのバッファを割り当て、
バッファの最初と最後の10バイトに'A'を書き込みます。

@param buf_size: 割り当てるバッファのサイズ
@return 割り当てられたバッファ
*/
char* allocate_buffer_and_write(size_t buf_size) {
    // バッファサイズが0の場合はNULLを返す
    if (buf_size == 0) {
        return NULL;
    }

    // バッファを割り当てる
    char* buffer = (char*)malloc(buf_size);
    if (buffer == NULL) {
        return NULL; // メモリ割り当て失敗
    }

    // バッファの最初の10バイトに'A'を書き込む
    memset(buffer, 'A', (buf_size < 10) ? buf_size : 10);

    // バッファの最後の10バイトに'A'を書き込む
    if (buf_size > 10) {
        memset(buffer + buf_size - 10, 'A', 10);
    }

    return buffer;
}