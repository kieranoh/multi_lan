#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <fcntl.h>
#include <unistd.h>
#include <errno.h>

void save_secrete_file(const char *directory, const char *filename, const char *content) {
    // Validar paràmetres d'entrada
    if (directory == NULL || filename == NULL || content == NULL) {
        fprintf(stderr, "Error: Paràmetres invàlids (NULL)\n");
        return;
    }
    
    // Construir el camí complet del fitxer
    size_t dir_len = strlen(directory);
    size_t file_len = strlen(filename);
    
    // Verificar que el directori no acabi amb '/'
    int needs_separator = 0;
    if (dir_len > 0 && directory[dir_len - 1] != '/') {
        needs_separator = 1;
    }
    
    // Calcular la mida necessària per al camí complet
    size_t full_path_len = dir_len + needs_separator + file_len + 1;
    char *full_path = (char *)malloc(full_path_len);
    if (full_path == NULL) {
        fprintf(stderr, "Error: No s'ha pogut assignar memòria\n");
        return;
    }
    
    // Construir el camí complet
    strcpy(full_path, directory);
    if (needs_separator) {
        strcat(full_path, "/");
    }
    strcat(full_path, filename);
    
    // Crear el directori si no existeix (amb permisos restringits)
    if (mkdir(directory, 0700) == -1) {
        if (errno != EEXIST) {
            fprintf(stderr, "Error: No s'ha pogut crear/obrir el directori '%s': %s\n", 
                    directory, strerror(errno));
            free(full_path);
            return;
        }
    } else {
        // Si hem creat el directori, assegurar-nos que només l'usuari actual hi tingui accés
        if (chmod(directory, 0700) == -1) {
            fprintf(stderr, "Advertència: No s'han pogut establir els permisos del directori: %s\n",
                    strerror(errno));
        }
    }
    
    // Obrir el fitxer amb permisos restringits (només lectura/escriptura per l'usuari)
    int fd = open(full_path, O_WRONLY | O_CREAT | O_TRUNC, 0600);
    if (fd == -1) {
        fprintf(stderr, "Error: No s'ha pogut crear el fitxer '%s': %s\n", 
                full_path, strerror(errno));
        free(full_path);
        return;
    }
    
    // Escriure el contingut al fitxer
    size_t content_len = strlen(content);
    ssize_t bytes_written = write(fd, content, content_len);
    
    if (bytes_written == -1) {
        fprintf(stderr, "Error: No s'ha pogut escriure al fitxer: %s\n", strerror(errno));
    } else if ((size_t)bytes_written != content_len) {
        fprintf(stderr, "Advertència: No s'ha escrit tot el contingut (%zd de %zu bytes)\n",
                bytes_written, content_len);
    }
    
    // Tancar el fitxer
    if (close(fd) == -1) {
        fprintf(stderr, "Advertència: Error en tancar el fitxer: %s\n", strerror(errno));
    }
    
    // Assegurar-nos que els permisos del fitxer són correctes (en cas que open() no ho hagi fet bé)
    if (chmod(full_path, 0600) == -1) {
        fprintf(stderr, "Advertència: No s'han pogut establir els permisos del fitxer: %s\n",
                strerror(errno));
    }
    
    // Alliberar memòria
    free(full_path);
}