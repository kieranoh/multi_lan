#include <archive.h>
#include <archive_entry.h>
#include <string>
#include <cstring>

bool extract_tar_to_path(const std::string& tar_path, const std::string& dest_path) {
    struct archive *src = nullptr;
    struct archive *out = nullptr;
    struct archive_entry *entry = nullptr;
    int flags = 0;
    int r;

    // Inizializza il reader dell'archivio
    src = archive_read_new();
    if (!src) {
        return false;
    }
    
    // Supporta vari formati di compressione
    archive_read_support_format_all(src);
    archive_read_support_filter_all(src);

    // Apri il file tar
    r = archive_read_open_filename(src, tar_path.c_str(), 10240);
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
    
    // Imposta le opzioni per l'estrazione
    flags = ARCHIVE_EXTRACT_TIME | ARCHIVE_EXTRACT_PERM | ARCHIVE_EXTRACT_ACL | 
            ARCHIVE_EXTRACT_FFLAGS | ARCHIVE_EXTRACT_SECURE_SYMLINKS |
            ARCHIVE_EXTRACT_SECURE_NODOTDOT;
    archive_write_disk_set_options(out, flags);
    archive_write_disk_set_standard_lookup(out);

    // Leggi ed estrai ogni voce
    while ((r = archive_read_next_header(src, &entry)) == ARCHIVE_OK) {
        // Crea il percorso completo
        std::string full_path = dest_path + "/" + archive_entry_pathname(entry);
        archive_entry_set_pathname(entry, full_path.c_str());

        // Scrivi l'intestazione
        r = archive_write_header(out, entry);
        if (r != ARCHIVE_OK) {
            archive_write_free(out);
            archive_read_free(src);
            return false;
        }

        // Copia i dati se la voce ha contenuto
        if (archive_entry_size(entry) > 0) {
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
        }

        // Finalizza la voce
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
    return (r == ARCHIVE_EOF);
}