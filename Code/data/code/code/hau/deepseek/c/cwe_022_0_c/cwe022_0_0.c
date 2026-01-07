#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <dirent.h>
#include <sys/stat.h>
#include <errno.h>

char *read_file_from_dir(const char *filename, const char *dir_path) {
    // Validate input parameters
    if (filename == NULL || dir_path == NULL || filename[0] == '\0' || dir_path[0] == '\0') {
        return strdup("");
    }
    
    // Construct full path
    size_t dir_len = strlen(dir_path);
    size_t file_len = strlen(filename);
    
    // Check for potential buffer overflow
    if (dir_len > PATH_MAX || file_len > PATH_MAX || (dir_len + file_len + 2) > PATH_MAX) {
        return strdup("");
    }
    
    char full_path[PATH_MAX];
    
    // Handle directory path formatting
    if (dir_path[dir_len - 1] == '/') {
        snprintf(full_path, sizeof(full_path), "%s%s", dir_path, filename);
    } else {
        snprintf(full_path, sizeof(full_path), "%s/%s", dir_path, filename);
    }
    
    // Open the file
    FILE *file = fopen(full_path, "rb");
    if (file == NULL) {
        return strdup("");
    }
    
    // Get file size
    if (fseek(file, 0, SEEK_END) != 0) {
        fclose(file);
        return strdup("");
    }
    
    long file_size = ftell(file);
    if (file_size < 0) {
        fclose(file);
        return strdup("");
    }
    
    rewind(file);
    
    // Allocate buffer for file content
    char *content = (char *)malloc(file_size + 1);
    if (content == NULL) {
        fclose(file);
        return strdup("");
    }
    
    // Read file content
    size_t bytes_read = fread(content, 1, file_size, file);
    if (bytes_read != (size_t)file_size) {
        free(content);
        fclose(file);
        return strdup("");
    }
    
    // Null-terminate the string
    content[file_size] = '\0';
    
    fclose(file);
    return content;
}