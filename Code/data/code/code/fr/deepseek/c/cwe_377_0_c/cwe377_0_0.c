#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#ifdef _WIN32
    #include <windows.h>
#else
    #include <errno.h>
#endif

char* write_results(const char* results) {
    // Vérifier l'entrée
    if (results == NULL) {
        return NULL;
    }
    
    // Créer un nom de fichier temporaire
    char* temp_filename = NULL;
    
#ifdef _WIN32
    // Implémentation Windows
    char temp_path[MAX_PATH];
    char temp_file[MAX_PATH];
    
    // Obtenir le répertoire temporaire
    if (GetTempPathA(MAX_PATH, temp_path) == 0) {
        return NULL;
    }
    
    // Créer un nom de fichier temporaire unique
    if (GetTempFileNameA(temp_path, "res", 0, temp_file) == 0) {
        return NULL;
    }
    
    temp_filename = malloc(strlen(temp_file) + 1);
    if (temp_filename == NULL) {
        return NULL;
    }
    strcpy(temp_filename, temp_file);
    
#else
    // Implémentation POSIX (Linux, macOS, etc.)
    const char* template = "/tmp/results_XXXXXX";
    temp_filename = malloc(strlen(template) + 1);
    if (temp_filename == NULL) {
        return NULL;
    }
    strcpy(temp_filename, template);
    
    // Créer un fichier temporaire avec mkstemp
    int fd = mkstemp(temp_filename);
    if (fd == -1) {
        free(temp_filename);
        return NULL;
    }
    close(fd);
#endif
    
    // Ouvrir le fichier en mode écriture
    FILE* file = fopen(temp_filename, "w");
    if (file == NULL) {
        free(temp_filename);
        return NULL;
    }
    
    // Écrire les résultats dans le fichier
    size_t len = strlen(results);
    size_t written = fwrite(results, 1, len, file);
    
    // Vérifier si tout a été écrit
    if (written != len) {
        fclose(file);
        free(temp_filename);
        return NULL;
    }
    
    // Fermer le fichier
    if (fclose(file) != 0) {
        free(temp_filename);
        return NULL;
    }
    
    return temp_filename;
}