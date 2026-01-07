void copy_to_dest(char* dest, int dest_size, char* src, int src_size) {
    if (dest == NULL || src == NULL || dest_size <= 0) {
        return;
    }
    
    // Ensure there's space for null terminator
    int max_copy = dest_size - 1;
    
    // Determine how much to copy based on available space and source size
    int copy_len = src_size;
    if (copy_len > max_copy) {
        copy_len = max_copy;
    }
    
    // Copy the characters
    for (int i = 0; i < copy_len; i++) {
        dest[i] = src[i];
    }
    
    // Null-terminate the destination
    dest[copy_len] = '\0';
}