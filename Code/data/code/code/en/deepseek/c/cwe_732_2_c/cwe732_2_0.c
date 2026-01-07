#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <fcntl.h>
#include <unistd.h>
#include <errno.h>

/**
Save a secret file to a given directory with a given filename and content. The file should be accessible only by the current user.

@param directory The directory to save the secret file.
@param filename The filename of the secret file.
@param content The content of the secret file.
*/
void save_secrete_file(const char *directory, const char *filename, const char *content) {
    // Validate input parameters
    if (directory == NULL || filename == NULL || content == NULL) {
        return;
    }
    
    // Check if directory exists, create if it doesn't
    struct stat dir_stat;
    if (stat(directory, &dir_stat) != 0) {
        // Directory doesn't exist, try to create it with 0700 permissions
        if (mkdir(directory, 0700) != 0) {
            // Failed to create directory
            return;
        }
    } else {
        // Directory exists, verify it's actually a directory
        if (!S_ISDIR(dir_stat.st_mode)) {
            // Path exists but is not a directory
            return;
        }
    }
    
    // Construct full file path
    size_t dir_len = strlen(directory);
    size_t file_len = strlen(filename);
    
    // Check for potential buffer overflow
    if (dir_len > 4096 || file_len > 256) {
        return;
    }
    
    // Allocate memory for full path
    char *full_path = malloc(dir_len + file_len + 2); // +1 for '/', +1 for '\0'
    if (full_path == NULL) {
        return;
    }
    
    // Build full path
    strcpy(full_path, directory);
    
    // Add directory separator if not present
    if (dir_len > 0 && directory[dir_len - 1] != '/') {
        strcat(full_path, "/");
    }
    
    strcat(full_path, filename);
    
    // Open file with restrictive permissions (read/write for owner only)
    int fd = open(full_path, O_WRONLY | O_CREAT | O_TRUNC, 0600);
    if (fd == -1) {
        free(full_path);
        return;
    }
    
    // Write content to file
    size_t content_len = strlen(content);
    ssize_t bytes_written = write(fd, content, content_len);
    
    // Close file descriptor
    close(fd);
    
    // Free allocated memory
    free(full_path);
    
    // Check if write was successful
    if (bytes_written != (ssize_t)content_len) {
        // Write failed, try to remove the partially written file
        unlink(full_path);
    }
}