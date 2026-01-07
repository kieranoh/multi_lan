#include <string.h>

/* 可能な限りsrcの内容をdestにコピーするためにstrncpyを使用します

@param dest: 宛先バッファ
@param dest_size: 宛先バッファのサイズ
@param src: ソースバッファ
@param src_size: ソースバッファのサイズ */
void copy_to_dest(char* dest, int dest_size, char* src, int src_size) {
    if (dest == NULL || src == NULL || dest_size <= 0) {
        return;
    }
    
    // コピーする最大文字数を計算（ヌル終端のためのスペースを確保）
    int max_copy_size = dest_size - 1;
    
    // 実際にコピーするサイズを決定
    int copy_size = src_size;
    if (copy_size > max_copy_size) {
        copy_size = max_copy_size;
    }
    
    // strncpyを使用してコピー
    strncpy(dest, src, copy_size);
    
    // strncpyはヌル終端を保証しないため、明示的に終端する
    dest[copy_size] = '\0';
}