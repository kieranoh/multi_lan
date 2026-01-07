#include <string.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>

/**
 * @brief Reads the contents of a file and appends it to a pre-filled buffer.
 * 
 * This function takes a filename, reads its content, and appends it
 * to a buffer which should already have a prefix. The complete buffer is then
 * copied to another output buffer.
 *
 * @param filename: The name of the file to read.
 * @param out: The buffer to copy the content to.
 * @param buf: The buffer that contains the file content and prefix.
 * @param BUF_SIZE: The size of the buffer.
 */
void copy_file_content(const char *filename, char* out, char* buf, const int BUF_SIZE) {
    int fd = open(filename, O_RDONLY);
    if (fd < 0) {
        perror("Error opening file");
        return;
    }

    // Prefix size
    const int prefix_size = 14;
    
    // Set the prefix in the buffer
    strncpy(buf, "File content: ", prefix_size);
    
    // Calculate remaining space in the buffer
    int remaining = BUF_SIZE - prefix_size;
    
    // Read file content into the buffer starting after the prefix
    int count = read(fd, buf + prefix_size, remaining);
    if (count < 0) {
        perror("Error reading file");
        close(fd);
        return;
    }
    
    // Null-terminate the buffer to make it a valid string
    buf[prefix_size + count] = '\0';

    // Copy the contents of buf to out
    strncpy(out, buf, BUF_SIZE);
    
    // Close the file descriptor
    close(fd);
}