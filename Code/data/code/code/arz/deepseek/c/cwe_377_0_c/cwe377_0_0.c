#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <errno.h>

#ifdef _WIN32
#include <windows.h>
#else
#include <sys/types.h>
#include <sys/stat.h>
#endif

char* write_results(const char* results) {
    if (results == NULL) {
        return NULL;
    }
    
    char* filename = NULL;
    
#ifdef _WIN32
    /* Windows: Verwenden Sie GetTempPath und GetTempFileName */
    char temp_path[MAX_PATH];
    char temp_filename[MAX_PATH];
    
    if (GetTempPathA(MAX_PATH, temp_path) == 0) {
        return NULL;
    }
    
    if (GetTempFileNameA(temp_path, "res", 0, temp_filename) == 0) {
        return NULL;
    }
    
    filename = malloc(strlen(temp_filename) + 1);
    if (filename == NULL) {
        return NULL;
    }
    strcpy(filename, temp_filename);
#else
    /* Unix-ähnliche Systeme: Verwenden Sie mkstemp */
    char template[] = "/tmp/resultsXXXXXX";
    int fd = mkstemp(template);
    if (fd == -1) {
        return NULL;
    }
    
    filename = malloc(strlen(template) + 1);
    if (filename == NULL) {
        close(fd);
        return NULL;
    }
    strcpy(filename, template);
    close(fd);
#endif
    
    /* Ergebnisse in die Datei schreiben */
    FILE* file = fopen(filename, "w");
    if (file == NULL) {
        free(filename);
        return NULL;
    }
    
    size_t results_len = strlen(results);
    size_t written = fwrite(results, 1, results_len, file);
    
    if (written != results_len) {
        fclose(file);
        free(filename);
        return NULL;
    }
    
    if (fclose(file) != 0) {
        free(filename);
        return NULL;
    }
    
    return filename;
}