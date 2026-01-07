#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <errno.h>

#ifdef _WIN32
    #include <windows.h>
    #define PATH_SEPARATOR '\\'
#else
    #include <unistd.h>
    #define PATH_SEPARATOR '/'
#endif

char *read_file_from_dir(const char *filename, const char *dir_path) {
    // Validate input parameters
    if (filename == NULL || dir_path == NULL) {
        return strdup("");
    }
    
    // Check if filename is empty
    if (strlen(filename) == 0) {
        return strdup("");
    }
    
    // Construct full file path
    size_t dir_len = strlen(dir_path);
    size_t filename_len = strlen(filename);
    
    // Ensure dir_path ends with a separator
    int needs_separator = 0;
    if (dir_len > 0 && dir_path[dir_len - 1] != PATH_SEPARATOR) {
        needs_separator = 1;
    }
    
    // Allocate memory for full path
    size_t full_path_len = dir_len + needs_separator + filename_len + 1;
    char *full_path = (char *)malloc(full_path_len);
    if (full_path == NULL) {
        return strdup("");
    }
    
    // Build full path
    strcpy(full_path, dir_path);
    if (needs_separator) {
        strcat(full_path, (char[]){PATH_SEPARATOR, '\0'});
    }
    strcat(full_path, filename);
    
    // Check if file exists and is accessible
    FILE *file = fopen(full_path, "rb");
    if (file == NULL) {
        free(full_path);
        return strdup("");
    }
    
    // Get file size
    if (fseek(file, 0, SEEK_END) != 0) {
        fclose(file);
        free(full_path);
        return strdup("");
    }
    
    long file_size = ftell(file);
    if (file_size < 0) {
        fclose(file);
        free(full_path);
        return strdup("");
    }
    
    rewind(file);
    
    // Allocate memory for file content (plus null terminator)
    char *content = (char *)malloc(file_size + 1);
    if (content == NULL) {
        fclose(file);
        free(full_path);
        return strdup("");
    }
    
    // Read file content
    size_t bytes_read = fread(content, 1, file_size, file);
    if (bytes_read != (size_t)file_size) {
        free(content);
        fclose(file);
        free(full_path);
        return strdup("");
    }
    
    // Null-terminate the string
    content[file_size] = '\0';
    
    // Clean up
    fclose(file);
    free(full_path);
    
    return content;
}