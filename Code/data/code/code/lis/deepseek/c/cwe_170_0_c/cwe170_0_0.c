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
    
    // Copy the prefix to the buffer
    strcpy(buf, "File content: ");
    
    // Calculate remaining space after the prefix
    int remaining = BUF_SIZE - 14;
    if (remaining <= 0) {
        // If no space left for file content, just copy what we have
        strncpy(out, buf, BUF_SIZE);
        close(fd);
        return;
    }
    
    // Read file content into buffer after the prefix
    int count = read(fd, buf + 14, remaining);
    if (count < 0) {
        perror("Error reading file");
        close(fd);
        return;
    }
    
    // Null-terminate the buffer if there's space
    if (14 + count < BUF_SIZE) {
        buf[14 + count] = '\0';
    } else {
        buf[BUF_SIZE - 1] = '\0';
    }
    
    // Copy all contents from buf to out
    strncpy(out, buf, BUF_SIZE);
    out[BUF_SIZE - 1] = '\0'; // Ensure null termination
    
    close(fd);
}