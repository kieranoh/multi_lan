#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char *read_file_from_dir(const char *filename, const char *dir_path) {
    // The full path of the file
    char full_path[1024];
    snprintf(full_path, sizeof(full_path), "%s/%s", dir_path, filename);

    // Open the file for reading
    FILE *file = fopen(full_path, "r");
    if (file == NULL) {
        // Return an empty string on error (file not found, permission denied, etc.)
        return strdup("");
    }

    // Read the contents of the file
    fseek(file, 0, SEEK_END);
    long file_size = ftell(file);
    fseek(file, 0, SEEK_SET);

    // Allocate memory for the contents + 1 for the null terminator
    char *content = (char *)malloc(file_size + 1);
    if (content == NULL) {
        fclose(file);
        return strdup(""); // Return empty string if memory allocation fails
    }

    // Read the file contents into the allocated memory
    fread(content, 1, file_size, file);
    content[file_size] = '\0'; // Null-terminate the string

    // Close the file
    fclose(file);
    
    return content; // Return the content
}