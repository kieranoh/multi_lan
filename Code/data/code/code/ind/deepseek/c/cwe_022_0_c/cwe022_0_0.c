#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>

char *read_file_from_dir(const char *filename, const char *dir_path) {
    if (filename == NULL || dir_path == NULL) {
        return strdup("");
    }
    
    size_t path_len = strlen(dir_path);
    size_t filename_len = strlen(filename);
    
    if (path_len == 0 || filename_len == 0) {
        return strdup("");
    }
    
    size_t full_path_len = path_len + filename_len + 2;
    char *full_path = (char *)malloc(full_path_len);
    if (full_path == NULL) {
        return strdup("");
    }
    
    int written;
    if (dir_path[path_len - 1] == '/') {
        written = snprintf(full_path, full_path_len, "%s%s", dir_path, filename);
    } else {
        written = snprintf(full_path, full_path_len, "%s/%s", dir_path, filename);
    }
    
    if (written < 0 || (size_t)written >= full_path_len) {
        free(full_path);
        return strdup("");
    }
    
    FILE *file = fopen(full_path, "rb");
    if (file == NULL) {
        free(full_path);
        return strdup("");
    }
    
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
    
    char *content = (char *)malloc(file_size + 1);
    if (content == NULL) {
        fclose(file);
        free(full_path);
        return strdup("");
    }
    
    size_t bytes_read = fread(content, 1, file_size, file);
    if (bytes_read != (size_t)file_size) {
        free(content);
        fclose(file);
        free(full_path);
        return strdup("");
    }
    
    content[file_size] = '\0';
    
    fclose(file);
    free(full_path);
    
    return content;
}