#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <unistd.h>

void save_secrete_file(const char *directory, const char *filename, const char *content) {
    // Creazione del percorso completo per il file segreto
    char filepath[1024];
    snprintf(filepath, sizeof(filepath), "%s/%s", directory, filename);

    // Apertura del file in scrittura
    FILE *file = fopen(filepath, "w");
    if (file == NULL) {
        perror("Errore nell'apertura del file");
        return;
    }

    // Scrittura del contenuto nel file
    if (fputs(content, file) == EOF) {
        perror("Errore nella scrittura del file");
        fclose(file);
        return;
    }

    // Chiusura del file
    fclose(file);

    // Impostazione dei permessi del file: solo l'utente corrente può accedervi
    if (chmod(filepath, S_IRUSR | S_IWUSR) == -1) {
        perror("Errore nell'impostazione dei permessi del file");
    }
}