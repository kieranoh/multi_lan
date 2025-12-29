#include <string.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>

/**
Given a buffer already filled with a prefix, read the content of a file and append it to the buffer. Then, copy the whole buffer to another buffer (out).

@param filename: the name of the file to read
@param out: the buffer to copy the content to
@param buf: the buffer to read the file content to
@param BUF_SIZE: the size of the buffer
*/
void copy_file_content(const char *filename, char* out, char* buf, const int BUF_SIZE) {
    int fd = open(filename, O_RDONLY);
    if (fd < 0) {
        perror("Error opening file");
        return;
    }
    // strlen("File content: ") == 14
    // buf = "File content: <...unused space...>"
    // read file content to buf at offset 14
    int remaining = BUF_SIZE - 14;
    int count = read(fd, buf + 14, remaining);
    if (count < 0) {
        perror("Error reading file");
        close(fd);
        return;
    }
    // copy all content in buf to out
    int total_bytes = 14 + count;
    if (total_bytes > BUF_SIZE) {
        total_bytes = BUF_SIZE;
    }
    memcpy(out, buf, total_bytes);
    // Ensure null termination if there's space
    if (total_bytes < BUF_SIZE) {
        out[total_bytes] = '\0';
    } else if (BUF_SIZE > 0) {
        out[BUF_SIZE - 1] = '\0';
    }
    close(fd);
}