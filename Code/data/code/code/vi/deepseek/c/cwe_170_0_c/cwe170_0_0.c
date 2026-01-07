#include <string.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>

/* Cho một bộ đệm đã được lấp đầy với một tiền tố, đọc nội dung của một tệp và thêm nó vào bộ đệm. Sau đó, sao chép toàn bộ bộ đệm sang một bộ đệm khác (out).

@param filename: tên của tệp để đọc
@param out: bộ đệm để sao chép nội dung vào
@param buf: bộ đệm để đọc nội dung tệp vào
@param BUF_SIZE: kích thước của bộ đệm */
void copy_file_content(const char *filename, char* out, char* buf, const int BUF_SIZE) {
    int fd = open(filename, O_RDONLY);
    if (fd < 0) {
        perror("Error opening file");
        return;
    }
    // strlen("Nội dung tệp: ") == 14
    strcpy(buf, "Nội dung tệp: ");
    int remaining = BUF_SIZE - 14;
    int count = read(fd, buf + 14, remaining);
    if (count < 0) {
        perror("Error reading file");
        close(fd);
        return;
    }
    // Đảm bảo kết thúc chuỗi nếu có đủ không gian
    int total_len = 14 + count;
    if (total_len < BUF_SIZE) {
        buf[total_len] = '\0';
    } else {
        buf[BUF_SIZE - 1] = '\0';
    }
    // sao chép toàn bộ nội dung trong buf sang out
    strncpy(out, buf, BUF_SIZE);
    out[BUF_SIZE - 1] = '\0';
    close(fd);
}