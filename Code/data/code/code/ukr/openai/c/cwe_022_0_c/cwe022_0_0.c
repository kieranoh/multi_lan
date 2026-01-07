#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char *read_file_from_dir(const char *filename, const char *dir_path) {
    // Create the full file path
    size_t path_length = strlen(dir_path) + strlen(filename) + 2; // +2 for '/' and '\0'
    char *full_path = (char *)malloc(path_length);
    
    if (full_path == NULL) {
        return NULL; // Return NULL if memory allocation fails
    }
    
    snprintf(full_path, path_length, "%s/%s", dir_path, filename);
    
    // Open the file for reading
    FILE *file = fopen(full_path, "r");
    free(full_path); // Free the allocated path after opening the file

    if (file == NULL) {
        return ""; // Return empty string on error
    }

    // Read the file content
    fseek(file, 0, SEEK_END);
    long file_size = ftell(file);
    fseek(file, 0, SEEK_SET);
    
    if (file_size < 0) {
        fclose(file);
        return ""; // Return empty string if unable to get file size
    }
    
    char *content = (char *)malloc(file_size + 1);
    
    if (content == NULL) {
        fclose(file);
        return ""; // Return empty string if memory allocation fails
    }
    
    fread(content, 1, file_size, file);
    content[file_size] = '\0'; // Null-terminate the string
    fclose(file);
    
    return content; // Return the content of the file
}