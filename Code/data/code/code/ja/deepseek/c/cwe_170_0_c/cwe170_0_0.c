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
    // strlen("File content: ") == 14
    // buf = "File content: <...unused space...>"
    // 14オフセットでbufにファイル内容を読み取る
    int remaining = BUF_SIZE - 14;
    int count = read(fd, buf + 14, remaining);
    if (count < 0) {
        perror("Error reading file");
        close(fd);
        return;
    }
    // bufの全内容をoutにコピーする
    int total_bytes = 14 + count;
    if (total_bytes > BUF_SIZE) {
        total_bytes = BUF_SIZE;
    }
    memcpy(out, buf, total_bytes);
    out[total_bytes] = '\0';
    close(fd);
}