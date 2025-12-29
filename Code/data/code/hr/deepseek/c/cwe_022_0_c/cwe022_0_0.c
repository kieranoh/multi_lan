#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>

#ifdef _WIN32
    #include <windows.h>
    #define PATH_SEPARATOR '\\'
#else
    #include <sys/stat.h>
    #include <unistd.h>
    #define PATH_SEPARATOR '/'
#endif

char *read_file_from_dir(const char *filename, const char *dir_path) {
    // Validate input parameters
    if (filename == NULL || dir_path == NULL || filename[0] == '\0') {
        return strdup("");
    }
    
    // Construct full file path
    size_t dir_len = strlen(dir_path);
    size_t filename_len = strlen(filename);
    
    // Check if directory path ends with separator
    int needs_separator = 0;
    if (dir_len > 0 && dir_path[dir_len - 1] != PATH_SEPARATOR) {
        needs_separator = 1;
    }
    
    // Allocate memory for full path
    char *full_path = malloc(dir_len + needs_separator + filename_len + 1);
    if (full_path == NULL) {
        return strdup("");
    }
    
    // Build full path
    strcpy(full_path, dir_path);
    if (needs_separator) {
        full_path[dir_len] = PATH_SEPARATOR;
        full_path[dir_len + 1] = '\0';
    }
    strcat(full_path, filename);
    
    // Try to open the file
    FILE *file = fopen(full_path, "rb");
    free(full_path);
    
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
    
    // Allocate memory for file content plus null terminator
    char *content = malloc(file_size + 1);
    if (content == NULL) {
        fclose(file);
        return strdup("");
    }
    
    // Read file content
    size_t bytes_read = fread(content, 1, file_size, file);
    content[bytes_read] = '\0';
    
    fclose(file);
    
    // Check if we read the entire file
    if (bytes_read != (size_t)file_size) {
        free(content);
        return strdup("");
    }
    
    return content;
}