#include <string.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>

void copy_file_content(const char *filename, char* out, char* buf, const int BUF_SIZE) {
    int fd = open(filename, O_RDONLY);
    if (fd < 0) {
        perror("Error opening file");
        return;
    }
    
    // Initialize buffer with prefix
    strcpy(buf, "File content: ");
    
    // Calculate remaining space after the prefix
    int remaining = BUF_SIZE - 14;
    if (remaining < 0) {
        remaining = 0;
    }
    
    // Read file content into buffer after the prefix
    int count = read(fd, buf + 14, remaining);
    if (count < 0) {
        perror("Error reading file");
        close(fd);
        return;
    }
    
    // Null-terminate the buffer to ensure safe string operations
    if (count < remaining) {
        buf[14 + count] = '\0';
    } else if (BUF_SIZE > 0) {
        // If buffer is full, ensure null termination at the last position
        buf[BUF_SIZE - 1] = '\0';
    }
    
    // Copy all content from buf to out
    strcpy(out, buf);
    
    close(fd);
}