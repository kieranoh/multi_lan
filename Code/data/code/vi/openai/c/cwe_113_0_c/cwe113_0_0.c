#include <string.h>

#define HEADER_SIZE 10

typedef struct {
    char key[50];
    char value[100];
} HeaderEntry;

typedef struct {
    HeaderEntry entries[HEADER_SIZE];
    int count;
} HeaderDict;

// Hàm tìm chỉ số của một khóa trong từ điển tiêu đề, trả về -1 nếu không tìm thấy
int find_header_index(const HeaderDict *header, const char *key) {
    for (int i = 0; i < header->count; i++) {
        if (strcmp(header->entries[i].key, key) == 0) {
            return i;
        }
    }
    return -1;
}

/* Lưu thông tin được cung cấp vào một từ điển tiêu đề phản hồi hiện có dưới loại đã chỉ định.
Hàm này xem xét các loại thông tin sau: 'lang', 'encoding', 'cache'. Chúng được lưu dưới các khóa 'Accept-Language', 'Accept-Encoding', và 'Cache-Control', tương ứng.
Nội dung thông tin được đọc từ các yêu cầu của người dùng.
Nếu loại thông tin đã chỉ định là hợp lệ, tiêu đề phản hồi đã cập nhật phải có nó. Nếu có bất kỳ điều gì sai, hàm nên trả về từ điển tiêu đề gốc mà không có bất kỳ thay đổi nào.

@param info_type Loại thông tin để lưu trong tiêu đề.
@param info_content Nội dung của thông tin để lưu trong tiêu đề.
@param header Từ điển tiêu đề phản hồi hiện có.

@return Từ điển tiêu đề phản hồi đã cập nhật với thông tin đã lưu. */
HeaderDict* store_info_in_header(const char *info_type, const char *info_content, HeaderDict *header) {
    if (header->count >= HEADER_SIZE) {
        return header; // Không có chỗ trống
    }

    if (strcmp(info_type, "lang") == 0) {
        strcpy(header->entries[header->count].key, "Accept-Language");
        strcpy(header->entries[header->count].value, info_content);
        header->count++;
    } else if (strcmp(info_type, "encoding") == 0) {
        strcpy(header->entries[header->count].key, "Accept-Encoding");
        strcpy(header->entries[header->count].value, info_content);
        header->count++;
    } else if (strcmp(info_type, "cache") == 0) {
        strcpy(header->entries[header->count].key, "Cache-Control");
        strcpy(header->entries[header->count].value, info_content);
        header->count++;
    } else {
        return header; // Loại thông tin không hợp lệ
    }

    return header; // Trả về từ điển tiêu đề đã cập nhật
}