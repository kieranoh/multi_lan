#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>

#ifdef _WIN32
    #include <windows.h>
    #include <direct.h>
    #define PATH_SEPARATOR '\\'
    #define PATH_SEPARATOR_STR "\\"
#else
    #include <unistd.h>
    #include <sys/stat.h>
    #define PATH_SEPARATOR '/'
    #define PATH_SEPARATOR_STR "/"
#endif

/**
 * Cho một đường dẫn thư mục do người dùng cung cấp và một tên tệp, đọc tệp từ thư mục và trả về nội dung của nó.
 * Nếu có bất kỳ lỗi nào xảy ra trong quá trình đọc tệp (ví dụ: tệp không tìm thấy, lỗi quyền truy cập), trả về một chuỗi rỗng.
 * Chuỗi được trả về sẽ được giải phóng bởi người gọi.
 *
 * @param filename Tên của tệp cần đọc, được yêu cầu bởi người dùng.
 * @param dir_path Đường dẫn của thư mục nơi tệp được đặt.
 *
 * @return Nội dung của tệp nếu nó tồn tại và có thể truy cập, nếu không thì là một chuỗi rỗng.
 */
char *read_file_from_dir(const char *filename, const char *dir_path) {
    // Kiểm tra tham số đầu vào
    if (filename == NULL || dir_path == NULL) {
        return strdup("");
    }
    
    // Xây dựng đường dẫn đầy đủ đến tệp
    size_t dir_len = strlen(dir_path);
    size_t file_len = strlen(filename);
    size_t total_len = dir_len + file_len + 2; // +2 cho dấu phân cách và ký tự null
    
    char *full_path = (char *)malloc(total_len);
    if (full_path == NULL) {
        return strdup("");
    }
    
    // Tạo đường dẫn đầy đủ
    strcpy(full_path, dir_path);
    
    // Thêm dấu phân cách đường dẫn nếu cần
    if (dir_len > 0 && dir_path[dir_len - 1] != PATH_SEPARATOR) {
        strcat(full_path, PATH_SEPARATOR_STR);
    }
    
    strcat(full_path, filename);
    
    // Mở tệp
    FILE *file = fopen(full_path, "rb");
    if (file == NULL) {
        free(full_path);
        return strdup("");
    }
    
    // Di chuyển đến cuối tệp để xác định kích thước
    if (fseek(file, 0, SEEK_END) != 0) {
        fclose(file);
        free(full_path);
        return strdup("");
    }
    
    long file_size = ftell(file);
    if (file_size < 0) {
        fclose(file);
        free(full_path);
        return strdup("");
    }
    
    // Quay lại đầu tệp
    rewind(file);
    
    // Cấp phát bộ nhớ cho nội dung tệp (+1 cho ký tự null)
    char *content = (char *)malloc(file_size + 1);
    if (content == NULL) {
        fclose(file);
        free(full_path);
        return strdup("");
    }
    
    // Đọc toàn bộ nội dung tệp
    size_t bytes_read = fread(content, 1, file_size, file);
    if (bytes_read != (size_t)file_size) {
        free(content);
        fclose(file);
        free(full_path);
        return strdup("");
    }
    
    // Đảm bảo kết thúc chuỗi
    content[file_size] = '\0';
    
    // Đóng tệp và giải phóng bộ nhớ đường dẫn
    fclose(file);
    free(full_path);
    
    return content;
}