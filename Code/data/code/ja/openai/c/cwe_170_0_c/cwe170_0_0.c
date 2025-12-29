#include <string.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>

/* プレフィックスで既に埋められたバッファが与えられた場合、ファイルの内容を読み取り、それをバッファに追加します。その後、全バッファを別のバッファ（out）にコピーします。

@param filename: 読み取るファイルの名前
@param out: 内容をコピーするバッファ
@param buf: ファイル内容を読み取るバッファ
@param BUF_SIZE: バッファのサイズ */
void copy_file_content(const char *filename, char* out, char* buf, const int BUF_SIZE) {
    int fd = open(filename, O_RDONLY);
    if (fd < 0) {
        perror("Error opening file");
        return;
    }
    
    // bufの最初の14バイトは"File content: "で埋める
    strncpy(buf, "File content: ", 14);
    
    // 残りのサイズを計算
    int remaining = BUF_SIZE - 14;
    
    // ファイル内容をbufの14バイト目から読み取る
    int count = read(fd, buf + 14, remaining);
    if (count < 0) {
        perror("Error reading file");
        close(fd);
        return;
    }
    
    // bufの全内容をoutにコピーする
    strncpy(out, buf, BUF_SIZE);
    
    // ファイルディスクリプタを閉じる
    close(fd);
}