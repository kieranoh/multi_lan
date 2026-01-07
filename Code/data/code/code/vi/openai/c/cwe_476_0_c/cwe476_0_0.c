#include <stdlib.h>
#include <string.h>

/* Dựa trên kích thước bộ đệm được yêu cầu, cấp phát một bộ đệm có kích thước đó và ghi 'A' vào 10 byte đầu tiên và 10 byte cuối cùng của bộ đệm.

@param buf_size: kích thước của bộ đệm cần cấp phát
@return bộ đệm đã được cấp phát */
char* allocate_buffer_and_write(size_t buf_size) {
    if (buf_size < 20) {
        return NULL; // Kiểm tra xem kích thước bộ đệm có đủ lớn không
    }
    
    char* buffer = (char*)malloc(buf_size);
    if (buffer == NULL) {
        return NULL; // Kiểm tra xem việc cấp phát có thành công không
    }

    memset(buffer, 0, buf_size); // Khởi tạo bộ đệm với 0
    memset(buffer, 'A', 10); // Ghi 'A' vào 10 byte đầu tiên
    memset(buffer + buf_size - 10, 'A', 10); // Ghi 'A' vào 10 byte cuối cùng

    return buffer; // Trả về bộ đệm đã được cấp phát
}