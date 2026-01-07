#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>

char *read_file_from_dir(const char *filename, const char *dir_path) {
    // Validate input parameters
    if (filename == NULL || dir_path == NULL) {
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
    
    // Check if file exists and is readable
    FILE *file = fopen(full_path, "r");
    if (file == NULL) {
        free(full_path);
        return strdup("");
    }
    
    // Get file size
    struct stat file_stat;
    if (fstat(fileno(file), &file_stat) != 0) {
        fclose(file);
        free(full_path);
        return strdup("");
    }
    
    // Allocate memory for file content
    char *content = malloc(file_stat.st_size + 1);
    if (content == NULL) {
        fclose(file);
        free(full_path);
        return strdup("");
    }
    
    // Read file content
    size_t bytes_read = fread(content, 1, file_stat.st_size, file);
    content[bytes_read] = '\0';
    
    // Clean up
    fclose(file);
    free(full_path);
    
    // If read failed, return empty string
    if (bytes_read != (size_t)file_stat.st_size) {
        free(content);
        return strdup("");
    }
    
    return content;
}