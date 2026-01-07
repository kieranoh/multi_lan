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
    
    // Copy the prefix to buf
    strcpy(buf, "File content: ");
    
    // Read file content starting from offset 14
    int remaining = BUF_SIZE - 14;
    int count = read(fd, buf + 14, remaining);
    if (count < 0) {
        perror("Error reading file");
        close(fd);
        return;
    }
    
    // Null-terminate the buffer if there's space
    if (count < remaining) {
        buf[14 + count] = '\0';
    } else if (BUF_SIZE > 0) {
        // Ensure null termination if buffer is full
        buf[BUF_SIZE - 1] = '\0';
    }
    
    // Copy all buf content to out
    strcpy(out, buf);
    
    close(fd);
}