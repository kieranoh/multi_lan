#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <fcntl.h>
#include <unistd.h>
#include <errno.h>

/* Salva un file segreto in una directory specificata con un nome file e contenuto dati. Il file dovrebbe essere accessibile solo dall'utente corrente.

@param directory La directory in cui salvare il file segreto.
@param filename Il nome del file segreto.
@param content Il contenuto del file segreto. */
void save_secrete_file(const char *directory, const char *filename, const char *content) {
    // Controllo dei parametri di input
    if (directory == NULL || filename == NULL || content == NULL) {
        fprintf(stderr, "Errore: parametri non validi (NULL)\n");
        return;
    }
    
    // Verifica che la directory esista, altrimenti prova a crearla
    struct stat dir_stat;
    if (stat(directory, &dir_stat) != 0) {
        // La directory non esiste, prova a crearla con permessi 0700 (solo proprietario)
        if (mkdir(directory, 0700) != 0) {
            fprintf(stderr, "Errore: impossibile creare la directory '%s': %s\n", 
                    directory, strerror(errno));
            return;
        }
    } else {
        // La directory esiste, verifica che sia effettivamente una directory
        if (!S_ISDIR(dir_stat.st_mode)) {
            fprintf(stderr, "Errore: '%s' non è una directory\n", directory);
            return;
        }
        
        // Verifica che la directory abbia permessi di scrittura per l'utente corrente
        if (access(directory, W_OK) != 0) {
            fprintf(stderr, "Errore: permessi di scrittura insufficienti per la directory '%s': %s\n",
                    directory, strerror(errno));
            return;
        }
    }
    
    // Costruisci il percorso completo del file
    size_t dir_len = strlen(directory);
    size_t file_len = strlen(filename);
    size_t total_len = dir_len + file_len + 2; // +2 per '/' e terminatore nullo
    
    char *full_path = (char *)malloc(total_len);
    if (full_path == NULL) {
        fprintf(stderr, "Errore: memoria insufficiente\n");
        return;
    }
    
    // Costruisci il percorso completo
    snprintf(full_path, total_len, "%s/%s", directory, filename);
    
    // Apri il file in modalità scrittura, creandolo se non esiste
    // O_WRONLY: sola scrittura
    // O_CREAT: crea il file se non esiste
    // O_TRUNC: tronca il file a lunghezza zero se esiste già
    // 0600: permessi -rw------- (solo proprietario può leggere e scrivere)
    int fd = open(full_path, O_WRONLY | O_CREAT | O_TRUNC, 0600);
    if (fd == -1) {
        fprintf(stderr, "Errore: impossibile creare/aprire il file '%s': %s\n",
                full_path, strerror(errno));
        free(full_path);
        return;
    }
    
    // Scrivi il contenuto nel file
    size_t content_len = strlen(content);
    ssize_t bytes_written = write(fd, content, content_len);
    
    if (bytes_written == -1) {
        fprintf(stderr, "Errore: impossibile scrivere nel file '%s': %s\n",
                full_path, strerror(errno));
        close(fd);
        free(full_path);
        return;
    }
    
    if ((size_t)bytes_written != content_len) {
        fprintf(stderr, "Attenzione: scritti solo %zd byte su %zu\n", 
                bytes_written, content_len);
    }
    
    // Chiudi il file
    if (close(fd) != 0) {
        fprintf(stderr, "Attenzione: errore durante la chiusura del file '%s': %s\n",
                full_path, strerror(errno));
    }
    
    // Verifica che i permessi siano corretti (in caso il file esistesse già con permessi diversi)
    if (chmod(full_path, 0600) != 0) {
        fprintf(stderr, "Attenzione: impossibile impostare i permessi del file '%s': %s\n",
                full_path, strerror(errno));
    }
    
    // Pulisci la memoria allocata
    free(full_path);
}