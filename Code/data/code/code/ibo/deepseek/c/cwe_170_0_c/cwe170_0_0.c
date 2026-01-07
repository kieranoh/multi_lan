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
    
    // Read file content starting at offset 14
    int remaining = BUF_SIZE - 14;
    if (remaining > 0) {
        int count = read(fd, buf + 14, remaining);
        if (count < 0) {
            perror("Error reading file");
            close(fd);
            return;
        }
        
        // Null-terminate the buffer if there's space
        if (14 + count < BUF_SIZE) {
            buf[14 + count] = '\0';
        } else if (BUF_SIZE > 0) {
            buf[BUF_SIZE - 1] = '\0';
        }
    } else if (BUF_SIZE > 0) {
        // Ensure buffer is properly terminated if no space for content
        buf[BUF_SIZE - 1] = '\0';
    }
    
    close(fd);
    
    // Copy all contents from buf to out
    strncpy(out, buf, BUF_SIZE);
    if (BUF_SIZE > 0) {
        out[BUF_SIZE - 1] = '\0';
    }
}