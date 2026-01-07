#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char *read_file_from_dir(const char *filename, const char *dir_path) {
    // Construct the full path
    size_t path_len = strlen(dir_path) + strlen(filename) + 2; // For '/' and null-terminator
    char *full_path = (char *)malloc(path_len);
    if (full_path == NULL) {
        return NULL; // Memory allocation failed
    }
    
    snprintf(full_path, path_len, "%s/%s", dir_path, filename);
    
    // Open the file for reading
    FILE *file = fopen(full_path, "r");
    free(full_path); // Free the full_path as it is no longer needed
    
    if (file == NULL) {
        return strdup(""); // Return empty string if file cannot be opened
    }
    
    // Read the file content
    fseek(file, 0, SEEK_END);
    long file_size = ftell(file);
    fseek(file, 0, SEEK_SET);
    
    char *content = (char *)malloc(file_size + 1); // +1 for null-terminator
    if (content == NULL) {
        fclose(file);
        return NULL; // Memory allocation failed
    }
    
    fread(content, 1, file_size, file);
    content[file_size] = '\0'; // Null-terminate the string
    
    fclose(file);
    return content; // Return the content of the file
}