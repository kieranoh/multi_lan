#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/stat.h>
#include <fcntl.h>

void save_secrete_file(const char *directory, const char *filename, const char *content) {
    // Create the full path for the secret file
    char filepath[1024];
    snprintf(filepath, sizeof(filepath), "%s/%s", directory, filename);

    // Open the file for writing (create if it doesn't exist)
    int fd = open(filepath, O_WRONLY | O_CREAT | O_TRUNC, S_IRUSR | S_IWUSR);
    if (fd < 0) {
        perror("Failed to open file");
        return;
    }

    // Write the content to the file
    ssize_t bytes_written = write(fd, content, strlen(content));
    if (bytes_written < 0) {
        perror("Failed to write to file");
    }

    // Close the file descriptor
    close(fd);
}