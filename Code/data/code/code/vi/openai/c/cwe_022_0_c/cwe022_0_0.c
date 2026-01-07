#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char *read_file_from_dir(const char *filename, const char *dir_path) {
    // Tạo đường dẫn đầy đủ đến tệp
    size_t path_length = strlen(dir_path) + strlen(filename) + 2; // +2 cho '/' và '\0'
    char *full_path = (char *)malloc(path_length);
    if (full_path == NULL) {
        return NULL; // Trả về NULL nếu không thể cấp phát bộ nhớ
    }

    snprintf(full_path, path_length, "%s/%s", dir_path, filename);
    
    // Mở tệp để đọc
    FILE *file = fopen(full_path, "r");
    free(full_path); // Giải phóng bộ nhớ cho full_path

    if (file == NULL) {
        return ""; // Trả về chuỗi rỗng nếu không thể mở tệp
    }

    // Đọc nội dung tệp
    fseek(file, 0, SEEK_END);
    long file_size = ftell(file);
    fseek(file, 0, SEEK_SET);

    char *content = (char *)malloc(file_size + 1); // +1 cho ký tự NULL
    if (content == NULL) {
        fclose(file);
        return NULL; // Trả về NULL nếu không thể cấp phát bộ nhớ
    }

    fread(content, 1, file_size, file);
    content[file_size] = '\0'; // Thêm ký tự NULL vào cuối chuỗi

    fclose(file);
    return content; // Trả về nội dung tệp
}