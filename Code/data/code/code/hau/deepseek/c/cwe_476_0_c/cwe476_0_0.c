char* allocate_buffer_and_write(size_t buf_size) {
    if (buf_size == 0) {
        return NULL;
    }
    
    char* buffer = (char*)malloc(buf_size);
    if (buffer == NULL) {
        return NULL;
    }
    
    // 처음 10바이트에 'A' 쓰기
    size_t first_write = (buf_size < 10) ? buf_size : 10;
    for (size_t i = 0; i < first_write; i++) {
        buffer[i] = 'A';
    }
    
    // 마지막 10바이트에 'A' 쓰기
    if (buf_size > 10) {
        size_t last_start = buf_size - 10;
        size_t last_write = (buf_size < 20) ? (buf_size - 10) : 10;
        for (size_t i = 0; i < last_write; i++) {
            buffer[last_start + i] = 'A';
        }
    }
    
    return buffer;
}