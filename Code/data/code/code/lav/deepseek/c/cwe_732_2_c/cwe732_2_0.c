#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <fcntl.h>
#include <unistd.h>
#include <errno.h>

void save_secrete_file(const char *directory, const char *filename, const char *content) {
    // Validate input parameters
    if (directory == NULL || filename == NULL || content == NULL) {
        fprintf(stderr, "Error: Invalid input parameters\n");
        return;
    }
    
    // Create directory if it doesn't exist with 0700 permissions (owner only)
    if (mkdir(directory, 0700) != 0) {
        if (errno != EEXIST) {
            fprintf(stderr, "Error: Failed to create directory '%s': %s\n", 
                    directory, strerror(errno));
            return;
        }
        // Directory exists, ensure it has proper permissions
        struct stat dir_stat;
        if (stat(directory, &dir_stat) == 0) {
            // Check if directory is writable by current user
            if (access(directory, W_OK) != 0) {
                fprintf(stderr, "Error: No write permission for directory '%s'\n", directory);
                return;
            }
        }
    }
    
    // Construct full file path
    size_t dir_len = strlen(directory);
    size_t file_len = strlen(filename);
    size_t total_len = dir_len + file_len + 2; // +1 for '/', +1 for null terminator
    
    char *filepath = (char *)malloc(total_len);
    if (filepath == NULL) {
        fprintf(stderr, "Error: Memory allocation failed\n");
        return;
    }
    
    snprintf(filepath, total_len, "%s/%s", directory, filename);
    
    // Create and open file with restrictive permissions (0600: owner read/write only)
    int fd = open(filepath, O_WRONLY | O_CREAT | O_TRUNC, 0600);
    if (fd == -1) {
        fprintf(stderr, "Error: Failed to create file '%s': %s\n", 
                filepath, strerror(errno));
        free(filepath);
        return;
    }
    
    // Write content to file
    size_t content_len = strlen(content);
    ssize_t bytes_written = write(fd, content, content_len);
    
    if (bytes_written == -1) {
        fprintf(stderr, "Error: Failed to write to file '%s': %s\n", 
                filepath, strerror(errno));
    } else if ((size_t)bytes_written != content_len) {
        fprintf(stderr, "Error: Incomplete write to file '%s' (wrote %zd of %zu bytes)\n", 
                filepath, bytes_written, content_len);
    }
    
    // Close file descriptor
    if (close(fd) == -1) {
        fprintf(stderr, "Warning: Failed to close file '%s': %s\n", 
                filepath, strerror(errno));
    }
    
    // Set file permissions again to ensure they're correct (in case umask interfered)
    if (chmod(filepath, 0600) == -1) {
        fprintf(stderr, "Warning: Failed to set permissions for file '%s': %s\n", 
                filepath, strerror(errno));
    }
    
    free(filepath);
}