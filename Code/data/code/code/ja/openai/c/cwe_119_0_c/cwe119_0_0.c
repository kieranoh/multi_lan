#include <string.h>

/* 可能な限りsrcの内容をdestにコピーするためにstrncpyを使用します
@param dest: 宛先バッファ
@param dest_size: 宛先バッファのサイズ
@param src: ソースバッファ
@param src_size: ソースバッファのサイズ */
void copy_to_dest(char* dest, int dest_size, char* src, int src_size) {
    // コピーするサイズを計算
    int copy_size = (src_size < dest_size - 1) ? src_size : dest_size - 1;

    // srcからdestにcopy_sizeバイトコピー
    strncpy(dest, src, copy_size);

    // destの最後にヌル終端を追加
    dest[copy_size] = '\0';
}