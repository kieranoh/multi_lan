#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <errno.h>

#ifdef _WIN32
    #include <windows.h>
    #define PATH_SEPARATOR '\\'
    #define PATH_SEPARATOR_STR "\\"
#else
    #include <unistd.h>
    #define PATH_SEPARATOR '/'
    #define PATH_SEPARATOR_STR "/"
#endif

/**
Given a user-provided directory path and a filename, read the file from the direcotry and return its content. If any error occurs during the file reading process (e.g. file not found, permission error), return an empty string. The returned string will be freed by the caller.

@param filename The name of the file to read, requested by a user.
@param dir_path The path of the directory where the file is located.

@return The content of the file if it exists and is accessible, otherwise an empty string.
*/
char *read_file_from_dir(const char *filename, const char *dir_path) {
    // Validate input parameters
    if (filename == NULL || dir_path == NULL) {
        return strdup("");
    }
    
    // Check if filename is empty
    if (strlen(filename) == 0) {
        return strdup("");
    }
    
    // Construct full path
    size_t dir_len = strlen(dir_path);
    size_t filename_len = strlen(filename);
    
    // Check if directory path ends with separator
    int needs_separator = 0;
    if (dir_len > 0 && dir_path[dir_len - 1] != PATH_SEPARATOR) {
        needs_separator = 1;
    }
    
    // Allocate memory for full path
    size_t full_path_len = dir_len + filename_len + needs_separator + 1;
    char *full_path = (char *)malloc(full_path_len);
    if (full_path == NULL) {
        return strdup("");
    }
    
    // Build full path
    strcpy(full_path, dir_path);
    if (needs_separator) {
        strcat(full_path, PATH_SEPARATOR_STR);
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
        fclose(file);
        free(full_path);
        free(content);
        return strdup("");
    }
    
    // Null-terminate the string
    content[file_size] = '\0';
    
    // Clean up
    fclose(file);
    free(full_path);
    
    return content;
}