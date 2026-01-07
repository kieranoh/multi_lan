#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <unistd.h>

void save_secrete_file(const char *directory, const char *filename, const char *content) {
    // Tạo đường dẫn đầy đủ cho tệp
    char filepath[1024];
    snprintf(filepath, sizeof(filepath), "%s/%s", directory, filename);

    // Mở tệp để ghi
    FILE *file = fopen(filepath, "w");
    if (file == NULL) {
        perror("Không thể mở tệp để ghi");
        return;
    }

    // Ghi nội dung vào tệp
    fprintf(file, "%s", content);
    fclose(file);

    // Đặt quyền truy cập chỉ cho người dùng hiện tại
    struct stat statbuf;
    stat(filepath, &statbuf);
    chmod(filepath, S_IRUSR | S_IWUSR);

    // Xác nhận rằng tệp đã được lưu thành công
    printf("Tệp bí mật đã được lưu thành công tại: %s\n", filepath);
}