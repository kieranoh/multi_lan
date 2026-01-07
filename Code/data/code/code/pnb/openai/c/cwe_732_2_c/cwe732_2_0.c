#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <unistd.h>
#include <fcntl.h>

void save_secrete_file(const char *directory, const char *filename, const char *content) {
    // Create file path
    char filepath[1024];
    snprintf(filepath, sizeof(filepath), "%s/%s", directory, filename);

    // Open the file for writing
    int fd = open(filepath, O_WRONLY | O_CREAT | O_TRUNC, S_IRUSR | S_IWUSR);
    if (fd == -1) {
        perror("Error opening file");
        return;
    }

    // Write content to the file
    if (write(fd, content, strlen(content)) == -1) {
        perror("Error writing to file");
    }

    // Close the file descriptor
    close(fd);

    // Set file permissions to owner only
    if (chmod(filepath, S_IRUSR | S_IWUSR) == -1) {
        perror("Error setting file permissions");
    }
}