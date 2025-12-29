#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <errno.h>

#ifdef _WIN32
    #include <windows.h>
    #define PATH_SEPARATOR '\\'
#else
    #include <unistd.h>
    #include <limits.h>
    #define PATH_SEPARATOR '/'
#endif

char *read_file_from_dir(const char *filename, const char *dir_path) {
    // Vérifier les paramètres d'entrée
    if (filename == NULL || dir_path == NULL) {
        return strdup("");
    }
    
    // Vérifier que le nom de fichier n'est pas vide
    if (strlen(filename) == 0) {
        return strdup("");
    }
    
    // Construire le chemin complet
    size_t dir_len = strlen(dir_path);
    size_t filename_len = strlen(filename);
    
    // Vérifier si le chemin du répertoire se termine par un séparateur
    int needs_separator = 0;
    if (dir_len > 0 && dir_path[dir_len - 1] != PATH_SEPARATOR) {
        needs_separator = 1;
    }
    
    // Allouer de la mémoire pour le chemin complet
    size_t full_path_len = dir_len + filename_len + needs_separator + 1;
    char *full_path = (char *)malloc(full_path_len);
    if (full_path == NULL) {
        return strdup("");
    }
    
    // Construire le chemin complet
    strcpy(full_path, dir_path);
    if (needs_separator) {
        strcat(full_path, (char[]){PATH_SEPARATOR, '\0'});
    }
    strcat(full_path, filename);
    
    // Vérifier si le fichier existe et est accessible
    FILE *file = fopen(full_path, "rb");  // Mode binaire pour la portabilité
    if (file == NULL) {
        free(full_path);
        return strdup("");
    }
    
    // Obtenir la taille du fichier
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
    
    // Revenir au début du fichier
    if (fseek(file, 0, SEEK_SET) != 0) {
        fclose(file);
        free(full_path);
        return strdup("");
    }
    
    // Allouer de la mémoire pour le contenu du fichier
    // +1 pour le caractère nul de fin
    char *content = (char *)malloc(file_size + 1);
    if (content == NULL) {
        fclose(file);
        free(full_path);
        return strdup("");
    }
    
    // Lire le contenu du fichier
    size_t bytes_read = fread(content, 1, file_size, file);
    if (bytes_read != (size_t)file_size) {
        free(content);
        fclose(file);
        free(full_path);
        return strdup("");
    }
    
    // Terminer la chaîne avec un caractère nul
    content[file_size] = '\0';
    
    // Nettoyer et retourner
    fclose(file);
    free(full_path);
    return content;
}