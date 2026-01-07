#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <errno.h>

#ifdef _WIN32
    #include <windows.h>
    #include <io.h>
    #define access _access
    #define F_OK 0
#else
    #include <unistd.h>
#endif

char* write_results(const char* results) {
    /* Ein temporäre Datei erstellen, die bereitgestellten Ergebnisse darin schreiben und den Dateinamen für weiteres Lesen zurückgeben. */
    
    if (results == NULL) {
        return NULL;
    }
    
    FILE *temp_file = NULL;
    char *filename = NULL;
    
    /* Eindeutigen Dateinamen generieren */
#ifdef _WIN32
    char temp_path[MAX_PATH];
    char temp_filename[MAX_PATH];
    
    /* Temporäres Verzeichnis abrufen */
    if (GetTempPathA(MAX_PATH, temp_path) == 0) {
        return NULL;
    }
    
    /* Eindeutigen Dateinamen generieren */
    if (GetTempFileNameA(temp_path, "res", 0, temp_filename) == 0) {
        return NULL;
    }
    
    filename = malloc(strlen(temp_filename) + 1);
    if (filename == NULL) {
        return NULL;
    }
    strcpy(filename, temp_filename);
#else
    /* Für Unix-ähnliche Systeme */
    const char *temp_dir = getenv("TMPDIR");
    if (temp_dir == NULL) {
        temp_dir = "/tmp";
    }
    
    /* Prüfen, ob das Verzeichnis existiert und beschreibbar ist */
    if (access(temp_dir, F_OK | W_OK) != 0) {
        return NULL;
    }
    
    /* Eindeutigen Dateinamen mit Zeitstempel und Zufallszahl generieren */
    filename = malloc(strlen(temp_dir) + 50);
    if (filename == NULL) {
        return NULL;
    }
    
    srand((unsigned int)time(NULL));
    int random_num = rand() % 10000;
    
    snprintf(filename, strlen(temp_dir) + 50, "%s/results_%ld_%d.tmp", 
             temp_dir, (long)time(NULL), random_num);
#endif
    
    /* Datei zum Schreiben öffnen */
    temp_file = fopen(filename, "w");
    if (temp_file == NULL) {
        free(filename);
        return NULL;
    }
    
    /* Ergebnisse in die Datei schreiben */
    size_t results_len = strlen(results);
    size_t written = fwrite(results, 1, results_len, temp_file);
    
    if (written != results_len) {
        fclose(temp_file);
        remove(filename);
        free(filename);
        return NULL;
    }
    
    /* Datei schließen */
    if (fclose(temp_file) != 0) {
        remove(filename);
        free(filename);
        return NULL;
    }
    
    return filename;
}