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
    
    // Đặt tiền tố vào đầu bộ đệm
    strcpy(buf, "Nội dung tệp: ");
    
    // Đọc nội dung tệp vào buf tại offset 14
    int remaining = BUF_SIZE - 14;
    int count = read(fd, buf + 14, remaining);
    if (count < 0) {
        perror("Error reading file");
        close(fd);
        return;
    }
    
    // Đóng tệp sau khi đọc
    close(fd);
    
    // Sao chép toàn bộ nội dung trong buf sang out
    strcpy(out, buf);
}