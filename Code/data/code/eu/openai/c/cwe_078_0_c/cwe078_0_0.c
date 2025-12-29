#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char *get_ls_result(const char *dir_path) {
    // Buffered output
    char *buffer = NULL;
    size_t size = 0;
    FILE *fp;
    
    // Create the command string
    char command[256];
    snprintf(command, sizeof(command), "ls -l %s", dir_path);

    // Open the command for reading
    fp = popen(command, "r");
    if (fp == NULL) {
        return "";  // Return an empty string if there is an error
    }

    // Read the output a line at a time - output it.
    buffer = malloc(1024);
    if (buffer == NULL) {
        pclose(fp);
        return "";  // Return an empty string if memory allocation fails
    }

    // Initialize an empty string
    size_t total_length = 0;

    // Read until end of file
    while (fgets(buffer, 1024, fp) != NULL) {
        size_t len = strlen(buffer);
        char *temp = realloc(buffer, total_length + len + 1);
        if (temp == NULL) {
            free(buffer);
            pclose(fp);
            return "";  // Return an empty string if memory allocation fails
        }
        buffer = temp;
        strcpy(buffer + total_length, buffer);
        total_length += len;
    }

    // Close the command stream
    pclose(fp);

    return buffer;  // Return the collected output
}