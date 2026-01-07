#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <errno.h>

char *read_file_from_dir(const char *filename, const char *dir_path) {
    // Validate input parameters
    if (filename == NULL || dir_path == NULL || filename[0] == '\0' || dir_path[0] == '\0') {
        return strdup("");
    }
    
    // Construct full file path
    size_t dir_len = strlen(dir_path);
    size_t filename_len = strlen(filename);
    
    // Check if directory path ends with '/'
    int needs_separator = 0;
    if (dir_len > 0 && dir_path[dir_len - 1] != '/') {
        needs_separator = 1;
    }
    
    // Allocate memory for full path
    char *full_path = malloc(dir_len + filename_len + needs_separator + 1);
    if (full_path == NULL) {
        return strdup("");
    }
    
    // Build full path
    strcpy(full_path, dir_path);
    if (needs_separator) {
        strcat(full_path, "/");
    }
    strcat(full_path, filename);
    
    // Check if file exists and is accessible
    struct stat file_stat;
    if (stat(full_path, &file_stat) != 0) {
        free(full_path);
        return strdup("");
    }
    
    // Check if it's a regular file
    if (!S_ISREG(file_stat.st_mode)) {
        free(full_path);
        return strdup("");
    }
    
    // Open the file
    FILE *file = fopen(full_path, "rb");
    if (file == NULL) {
        free(full_path);
        return strdup("");
    }
    
    // Get file size
    fseek(file, 0, SEEK_END);
    long file_size = ftell(file);
    fseek(file, 0, SEEK_SET);
    
    if (file_size < 0) {
        fclose(file);
        free(full_path);
        return strdup("");
    }
    
    // Allocate memory for file content plus null terminator
    char *content = malloc(file_size + 1);
    if (content == NULL) {
        fclose(file);
        free(full_path);
        return strdup("");
    }
    
    // Read file content
    size_t bytes_read = fread(content, 1, file_size, file);
    content[bytes_read] = '\0';  // Null-terminate the string
    
    // Clean up
    fclose(file);
    free(full_path);
    
    // If read failed, return empty string
    if (bytes_read != (size_t)file_size) {
        free(content);
        return strdup("");
    }
    
    return content;
}