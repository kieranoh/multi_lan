#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <fcntl.h>
#include <unistd.h>
#include <errno.h>

/* Lưu một tệp bí mật vào một thư mục nhất định với tên tệp và nội dung đã cho. Tệp này chỉ có thể được truy cập bởi người dùng hiện tại.

@param directory Thư mục để lưu tệp bí mật.
@param filename Tên tệp của tệp bí mật.
@param content Nội dung của tệp bí mật. */
void save_secrete_file(const char *directory, const char *filename, const char *content) {
    // Kiểm tra tham số đầu vào
    if (directory == NULL || filename == NULL || content == NULL) {
        fprintf(stderr, "Lỗi: Tham số không hợp lệ (NULL).\n");
        return;
    }
    
    // Tạo đường dẫn đầy đủ đến tệp
    size_t dir_len = strlen(directory);
    size_t file_len = strlen(filename);
    size_t path_len = dir_len + file_len + 2; // +2 cho '/' và '\0'
    
    char *full_path = (char *)malloc(path_len);
    if (full_path == NULL) {
        fprintf(stderr, "Lỗi: Không thể cấp phát bộ nhớ.\n");
        return;
    }
    
    // Tạo đường dẫn đầy đủ
    snprintf(full_path, path_len, "%s/%s", directory, filename);
    
    // Tạo thư mục nếu nó chưa tồn tại
    struct stat st = {0};
    if (stat(directory, &st) == -1) {
        // Thử tạo thư mục với quyền 0700 (chỉ người dùng hiện tại có quyền truy cập)
        if (mkdir(directory, 0700) == -1) {
            fprintf(stderr, "Lỗi: Không thể tạo thư mục '%s': %s\n", 
                    directory, strerror(errno));
            free(full_path);
            return;
        }
    } else {
        // Kiểm tra xem đường dẫn có phải là thư mục không
        if (!S_ISDIR(st.st_mode)) {
            fprintf(stderr, "Lỗi: '%s' không phải là thư mục.\n", directory);
            free(full_path);
            return;
        }
    }
    
    // Mở tệp để ghi, chỉ tạo mới nếu chưa tồn tại
    int fd = open(full_path, O_WRONLY | O_CREAT | O_TRUNC, 0600);
    if (fd == -1) {
        fprintf(stderr, "Lỗi: Không thể tạo tệp '%s': %s\n", 
                full_path, strerror(errno));
        free(full_path);
        return;
    }
    
    // Ghi nội dung vào tệp
    size_t content_len = strlen(content);
    ssize_t bytes_written = write(fd, content, content_len);
    
    if (bytes_written == -1) {
        fprintf(stderr, "Lỗi: Không thể ghi vào tệp '%s': %s\n", 
                full_path, strerror(errno));
    } else if ((size_t)bytes_written != content_len) {
        fprintf(stderr, "Cảnh báo: Chỉ ghi được %zd/%zu byte vào tệp '%s'\n", 
                bytes_written, content_len, full_path);
    }
    
    // Đóng tệp
    if (close(fd) == -1) {
        fprintf(stderr, "Cảnh báo: Lỗi khi đóng tệp '%s': %s\n", 
                full_path, strerror(errno));
    }
    
    // Giải phóng bộ nhớ
    free(full_path);
}