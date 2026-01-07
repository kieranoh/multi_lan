#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <errno.h>

#ifdef _WIN32
#include <windows.h>
#else
#include <sys/stat.h>
#endif

char* write_results(const char* results) {
    /* Ein temporäre Datei erstellen, die bereitgestellten Ergebnisse darin schreiben und den Dateinamen für weiteres Lesen zurückgeben. */
    
    if (results == NULL) {
        return NULL;
    }
    
    char* filename = NULL;
    FILE* temp_file = NULL;
    
#ifdef _WIN32
    /* Windows Implementierung */
    char temp_path[MAX_PATH];
    char temp_filename[MAX_PATH];
    
    /* Temporäres Verzeichnis holen */
    if (GetTempPathA(MAX_PATH, temp_path) == 0) {
        return NULL;
    }
    
    /* Eindeutigen temporären Dateinamen generieren */
    if (GetTempFileNameA(temp_path, "res", 0, temp_filename) == 0) {
        return NULL;
    }
    
    filename = malloc(strlen(temp_filename) + 1);
    if (filename == NULL) {
        return NULL;
    }
    strcpy(filename, temp_filename);
    
    /* Datei im Binärmodus öffnen um Zeilenumbruch-Konvertierung zu vermeiden */
    temp_file = fopen(filename, "wb");
    
#else
    /* Unix/Linux Implementierung */
    const char* temp_dir = NULL;
    
    /* Temporäres Verzeichnis bestimmen */
    temp_dir = getenv("TMPDIR");
    if (temp_dir == NULL) {
        temp_dir = getenv("TMP");
        if (temp_dir == NULL) {
            temp_dir = getenv("TEMP");
            if (temp_dir == NULL) {
                temp_dir = "/tmp";
            }
        }
    }
    
    /* Template für temporäre Datei erstellen */
    char template[1024];
    snprintf(template, sizeof(template), "%s/results_XXXXXX", temp_dir);
    
    /* Eindeutigen Dateinamen mit mkstemp erstellen */
    int fd = mkstemp(template);
    if (fd == -1) {
        return NULL;
    }
    
    /* Datei-Deskriptor in FILE* umwandeln */
    temp_file = fdopen(fd, "w");
    if (temp_file == NULL) {
        close(fd);
        return NULL;
    }
    
    filename = malloc(strlen(template) + 1);
    if (filename == NULL) {
        fclose(temp_file);
        return NULL;
    }
    strcpy(filename, template);
#endif
    
    if (temp_file == NULL) {
        free(filename);
        return NULL;
    }
    
    /* Ergebnisse in die Datei schreiben */
    size_t results_len = strlen(results);
    size_t written = fwrite(results, 1, results_len, temp_file);
    
    if (written != results_len) {
        fclose(temp_file);
        free(filename);
        return NULL;
    }
    
    /* Datei schließen */
    if (fclose(temp_file) != 0) {
        free(filename);
        return NULL;
    }
    
    return filename;
}