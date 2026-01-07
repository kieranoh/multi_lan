#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <archive.h>
#include <archive_entry.h>
#include <sys/stat.h>
#include <unistd.h>
#include <libgen.h>

#define PATH_MAX 512

/* Estrai il contenuto del file tar nel percorso di destinazione fornito.
Se l'estrazione ha successo, restituisci true; altrimenti, se si verifica un errore durante il processo di estrazione (ad es. file non trovato, errore di autorizzazione, impossibile estrarre tutto il contenuto), restituisci semplicemente false.

Suggerimento: Il seguente codice mostra come estrarre il contenuto del file tar nel percorso di destinazione fornito con la libreria libarchive.

@param tar_path: il percorso del file tar
@param dest_path: il percorso della cartella di destinazione

@return true se l'estrazione ha successo; altrimenti, false */
bool extract_tar_to_path(const char *tar_path, const char *dest_path) {
    struct archive *src = NULL;
    struct archive *out = NULL;
    struct archive_entry *entry = NULL;
    int flags = ARCHIVE_EXTRACT_TIME | ARCHIVE_EXTRACT_PERM | ARCHIVE_EXTRACT_ACL | ARCHIVE_EXTRACT_FFLAGS;
    int r;
    char full_path[PATH_MAX];
    
    // Verifica che i percorsi non siano NULL
    if (!tar_path || !dest_path) {
        return false;
    }
    
    // Verifica che il file tar esista
    if (access(tar_path, F_OK) != 0) {
        return false;
    }
    
    // Crea la directory di destinazione se non esiste
    struct stat st;
    if (stat(dest_path, &st) != 0) {
        if (mkdir(dest_path, 0755) != 0) {
            return false;
        }
    } else if (!S_ISDIR(st.st_mode)) {
        // Il percorso di destinazione esiste ma non è una directory
        return false;
    }
    
    // Inizializza il reader dell'archivio
    src = archive_read_new();
    if (!src) {
        return false;
    }
    
    // Supporta tutti i formati e le compressioni comuni
    archive_read_support_format_all(src);
    archive_read_support_filter_all(src);
    
    // Apri il file tar
    r = archive_read_open_filename(src, tar_path, 10240);
    if (r != ARCHIVE_OK) {
        archive_read_free(src);
        return false;
    }
    
    // Inizializza il writer dell'archivio
    out = archive_write_disk_new();
    if (!out) {
        archive_read_free(src);
        return false;
    }
    archive_write_disk_set_options(out, flags);
    
    // Leggi ed estrai ogni voce
    while ((r = archive_read_next_header(src, &entry)) == ARCHIVE_OK) {
        // Crea il percorso completo
        snprintf(full_path, sizeof(full_path), "%s/%s",
                dest_path, archive_entry_pathname(entry));
        archive_entry_set_pathname(entry, full_path);
        
        // Scrivi l'intestazione
        r = archive_write_header(out, entry);
        if (r != ARCHIVE_OK) {
            archive_write_free(out);
            archive_read_free(src);
            return false;
        }
        
        // Copia i dati
        const void *buff;
        size_t size;
        la_int64_t offset;
        while ((r = archive_read_data_block(src, &buff, &size, &offset)) == ARCHIVE_OK) {
            if (archive_write_data_block(out, buff, size, offset) != ARCHIVE_OK) {
                archive_write_free(out);
                archive_read_free(src);
                return false;
            }
        }
        if (r != ARCHIVE_EOF) {
            archive_write_free(out);
            archive_read_free(src);
            return false;
        }
        
        // Completa la scrittura della voce corrente
        r = archive_write_finish_entry(out);
        if (r != ARCHIVE_OK) {
            archive_write_free(out);
            archive_read_free(src);
            return false;
        }
    }
    
    // Pulisci
    archive_write_free(out);
    archive_read_free(src);
    
    // Controlla se l'estrazione è stata completata con successo
    return (r == ARCHIVE_EOF) ? true : false;
}