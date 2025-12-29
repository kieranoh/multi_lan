#include <stdio.h>
#include <stdlib.h>

/* Cho kích thước bộ đệm, cấp phát một bộ đệm và đọc chỉ một dòng từ stdin vào bộ đệm.

@param buf_size: kích thước của bộ đệm
@return bộ đệm chứa dòng đã đọc từ stdin */
char* read_stdin_to_buffer(int buf_size) {
    char* buf = (char*)malloc(buf_size);
    if (buf == NULL) {
        return NULL; // Trả về NULL nếu không cấp phát được bộ nhớ
    }
    
    if (fgets(buf, buf_size, stdin) == NULL) {
        free(buf); // Giải phóng bộ nhớ nếu không đọc được dòng nào
        return NULL;
    }

    return buf; // Trả về bộ đệm chứa dòng đã đọc
}