#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <errno.h>

char* write_results(const char* results) {
    /* Ein temporäre Datei erstellen, die bereitgestellten Ergebnisse darin schreiben und den Dateinamen für weiteres Lesen zurückgeben. */
    
    if (results == NULL) {
        return NULL;
    }
    
    /* Eindeutigen Dateinamen mit Zeitstempel generieren */
    time_t current_time = time(NULL);
    if (current_time == (time_t)-1) {
        return NULL;
    }
    
    struct tm* time_info = localtime(&current_time);
    if (time_info == NULL) {
        return NULL;
    }
    
    /* Dateinamen mit Präfix "results_" und Zeitstempel erstellen */
    char* filename = (char*)malloc(256 * sizeof(char));
    if (filename == NULL) {
        return NULL;
    }
    
    int written = snprintf(filename, 256, "results_%04d%02d%02d_%02d%02d%02d.tmp",
                          time_info->tm_year + 1900,
                          time_info->tm_mon + 1,
                          time_info->tm_mday,
                          time_info->tm_hour,
                          time_info->tm_min,
                          time_info->tm_sec);
    
    if (written < 0 || written >= 256) {
        free(filename);
        return NULL;
    }
    
    /* Datei im Binärmodus öffnen (um plattformübergreifende Zeilenumbruch-Probleme zu vermeiden) */
    FILE* file = fopen(filename, "wb");
    if (file == NULL) {
        free(filename);
        return NULL;
    }
    
    /* Ergebnisse in die Datei schreiben */
    size_t results_length = strlen(results);
    size_t bytes_written = fwrite(results, sizeof(char), results_length, file);
    
    /* Datei schließen */
    fclose(file);
    
    /* Überprüfen, ob alle Daten geschrieben wurden */
    if (bytes_written != results_length) {
        free(filename);
        return NULL;
    }
    
    return filename;
}