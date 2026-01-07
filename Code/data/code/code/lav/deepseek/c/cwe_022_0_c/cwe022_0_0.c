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
    size_t total_len = dir_len + 1 + filename_len + 1; // +1 for separator, +1 for null terminator
    
    char *full_path = (char *)malloc(total_len);
    if (full_path == NULL) {
        return strdup("");
    }
    
    // Build the path with appropriate separator
    strcpy(full_path, dir_path);
    
    // Add separator if needed
    if (dir_len > 0 && dir_path[dir_len - 1] != PATH_SEPARATOR) {
        full_path[dir_len] = PATH_SEPARATOR;
        full_path[dir_len + 1] = '\0';
    }
    
    strcat(full_path, filename);
    
    // Open the file
    FILE *file = fopen(full_path, "rb"); // Open in binary mode to handle all files
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
    
    // Allocate buffer for file content
    char *content = (char *)malloc(file_size + 1);
    if (content == NULL) {
        fclose(file);
        return strdup("");
    }
    
    // Read file content
    size_t bytes_read = fread(content, 1, file_size, file);
    content[bytes_read] = '\0'; // Null-terminate the string
    
    fclose(file);
    
    // If we didn't read the expected amount, treat as error
    if (bytes_read != (size_t)file_size) {
        free(content);
        return strdup("");
    }
    
    return content;
}