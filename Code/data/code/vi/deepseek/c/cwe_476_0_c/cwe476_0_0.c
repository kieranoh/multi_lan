#include <stdlib.h>
#include <string.h>
#include <stddef.h>

/* Dựa trên kích thước bộ đệm được yêu cầu, cấp phát một bộ đệm có kích thước đó và ghi 'A' vào 10 byte đầu tiên và 10 byte cuối cùng của bộ đệm.

@param buf_size: kích thước của bộ đệm cần cấp phát
@return bộ đệm đã được cấp phát */
char* allocate_buffer_and_write(size_t buf_size) {
    // Kiểm tra kích thước bộ đệm hợp lệ
    if (buf_size == 0) {
        return NULL;
    }
    
    // Cấp phát bộ đệm
    char* buffer = (char*)malloc(buf_size);
    if (buffer == NULL) {
        return NULL;
    }
    
    // Khởi tạo bộ đệm với giá trị 0 (tùy chọn, để dễ debug)
    memset(buffer, 0, buf_size);
    
    // Ghi 'A' vào 10 byte đầu tiên nếu bộ đệm đủ lớn
    size_t write_size = 10;
    if (buf_size >= write_size) {
        memset(buffer, 'A', write_size);
    } else {
        // Nếu bộ đệm nhỏ hơn 10 byte, ghi đầy toàn bộ bộ đệm
        memset(buffer, 'A', buf_size);
    }
    
    // Ghi 'A' vào 10 byte cuối cùng nếu bộ đệm đủ lớn
    if (buf_size >= write_size) {
        // Tính toán vị trí bắt đầu của 10 byte cuối cùng
        size_t start_pos = buf_size - write_size;
        memset(buffer + start_pos, 'A', write_size);
    } else {
        // Nếu bộ đệm nhỏ hơn 10 byte, đã ghi ở trên rồi
        // Không cần làm gì thêm
    }
    
    return buffer;
}