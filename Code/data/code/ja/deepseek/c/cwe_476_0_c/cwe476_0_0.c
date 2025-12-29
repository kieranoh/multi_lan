#include <stdlib.h>
#include <string.h>

/* 要求されたバッファサイズに基づいて、そのサイズのバッファを割り当て、バッファの最初と最後の10バイトに'A'を書き込みます。

@param buf_size: 割り当てるバッファのサイズ
@return 割り当てられたバッファ */
char* allocate_buffer_and_write(size_t buf_size) {
    if (buf_size == 0) {
        return NULL;
    }
    
    char* buffer = (char*)malloc(buf_size);
    if (buffer == NULL) {
        return NULL;
    }
    
    // バッファをゼロで初期化
    memset(buffer, 0, buf_size);
    
    // 最初の10バイトに'A'を書き込み
    size_t first_write_size = (buf_size < 10) ? buf_size : 10;
    memset(buffer, 'A', first_write_size);
    
    // 最後の10バイトに'A'を書き込み（最初の10バイトと重なる可能性がある）
    if (buf_size > 10) {
        size_t last_write_start = buf_size - 10;
        // 最後の10バイトが最初の10バイトと重ならないことを確認
        if (last_write_start >= 10) {
            memset(buffer + last_write_start, 'A', 10);
        } else {
            // 重なる場合は、最初の書き込み以降の部分のみ書き込む
            memset(buffer + 10, 'A', buf_size - 10);
        }
    }
    
    return buffer;
}