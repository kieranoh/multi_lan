#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define BUFFER_SIZE 1024

char *get_ls_result(const char *dir_path) {
    FILE *fp;
    char buffer[BUFFER_SIZE];
    char *result = NULL;
    size_t total_length = 0;

    // Create the command to execute
    char command[BUFFER_SIZE];
    snprintf(command, sizeof(command), "ls -l %s 2>/dev/null", dir_path);

    // Open the command for reading
    fp = popen(command, "r");
    if (fp == NULL) {
        return ""; // Return empty string on error
    }

    // Read the output a line at a time - output it.
    while (fgets(buffer, sizeof(buffer), fp) != NULL) {
        size_t length = strlen(buffer);
        char *new_result = realloc(result, total_length + length + 1);
        if (new_result == NULL) {
            free(result);
            pclose(fp);
            return ""; // Return empty string on memory allocation error
        }
        result = new_result;
        memcpy(result + total_length, buffer, length);
        total_length += length;
        result[total_length] = '\0'; // Null-terminate the string
    }

    // Close the command stream
    pclose(fp);
    return result; // Return the result
}