#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>
#include <fcntl.h>
#include <errno.h>

void save_secrete_file(const char *directory, const char *filename, const char *content) {
    if (directory == NULL || filename == NULL || content == NULL) {
        return;
    }

    // Create directory if it doesn't exist with 0700 permissions (owner only)
    if (mkdir(directory, 0700) != 0) {
        if (errno != EEXIST) {
            // Failed to create directory and it doesn't exist
            return;
        }
        // Directory exists, ensure it has secure permissions
        struct stat dir_stat;
        if (stat(directory, &dir_stat) == 0) {
            // Check if directory is secure (only owner has access)
            if ((dir_stat.st_mode & 0777) != 0700) {
                // Try to fix permissions
                chmod(directory, 0700);
            }
        }
    }

    // Construct full file path
    size_t dir_len = strlen(directory);
    size_t file_len = strlen(filename);
    
    // Check for trailing slash in directory
    int needs_slash = (dir_len > 0 && directory[dir_len - 1] != '/');
    
    // Allocate memory for full path
    char *full_path = malloc(dir_len + file_len + (needs_slash ? 2 : 1));
    if (full_path == NULL) {
        return;
    }
    
    strcpy(full_path, directory);
    if (needs_slash) {
        strcat(full_path, "/");
    }
    strcat(full_path, filename);

    // Create file with restrictive permissions (0600: owner read/write only)
    int fd = open(full_path, O_WRONLY | O_CREAT | O_TRUNC, 0600);
    if (fd == -1) {
        free(full_path);
        return;
    }

    // Write content to file
    size_t content_len = strlen(content);
    ssize_t written = write(fd, content, content_len);
    
    // Close file descriptor
    close(fd);
    
    // Ensure file permissions are correct (in case umask modified them)
    chmod(full_path, 0600);
    
    free(full_path);
}