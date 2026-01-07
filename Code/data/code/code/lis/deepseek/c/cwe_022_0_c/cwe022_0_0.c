#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <errno.h>

char *read_file_from_dir(const char *filename, const char *dir_path) {
    if (filename == NULL || dir_path == NULL) {
        return strdup("");
    }
    
    size_t dir_len = strlen(dir_path);
    size_t file_len = strlen(filename);
    
    if (dir_len == 0 || file_len == 0) {
        return strdup("");
    }
    
    int needs_separator = 0;
    if (dir_len > 0 && dir_path[dir_len - 1] != '/') {
        needs_separator = 1;
    }
    
    size_t full_path_len = dir_len + needs_separator + file_len + 1;
    char *full_path = (char *)malloc(full_path_len);
    if (full_path == NULL) {
        return strdup("");
    }
    
    if (needs_separator) {
        snprintf(full_path, full_path_len, "%s/%s", dir_path, filename);
    } else {
        snprintf(full_path, full_path_len, "%s%s", dir_path, filename);
    }
    
    FILE *file = fopen(full_path, "rb");
    free(full_path);
    
    if (file == NULL) {
        return strdup("");
    }
    
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
    
    char *content = (char *)malloc(file_size + 1);
    if (content == NULL) {
        fclose(file);
        return strdup("");
    }
    
    size_t bytes_read = fread(content, 1, file_size, file);
    content[bytes_read] = '\0';
    
    fclose(file);
    
    if (bytes_read != (size_t)file_size) {
        free(content);
        return strdup("");
    }
    
    return content;
}