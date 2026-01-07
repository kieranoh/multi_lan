#include <archive.h>
#include <archive_entry.h>
#include <string>
#include <cstdio>

bool extract_tar_to_path(const std::string& tar_path, const std::string& dest_path) {
    struct archive *src = archive_read_new();
    struct archive *out = archive_write_disk_new();
    struct archive_entry *entry;
    int flags = ARCHIVE_EXTRACT_TIME | ARCHIVE_EXTRACT_PERM;
    
    // Apri il file tar
    if (archive_read_open_filename(src, tar_path.c_str(), 10240) != ARCHIVE_OK) {
        archive_read_free(src);
        return false;
    }
    
    archive_write_disk_set_options(out, flags);
    
    // Leggi ed estrai ogni voce
    while (archive_read_next_header(src, &entry) == ARCHIVE_OK) {
        char full_path[1024];
        snprintf(full_path, sizeof(full_path), "%s/%s", dest_path.c_str(), archive_entry_pathname(entry));
        archive_entry_set_pathname(entry, full_path);
        
        // Scrivi l'intestazione
        if (archive_write_header(out, entry) != ARCHIVE_OK) {
            archive_read_free(src);
            archive_write_free(out);
            return false;
        }

        // Copia i dati
        const void *buff;
        size_t size;
        la_int64_t offset;
        while (archive_read_data_block(src, &buff, &size, &offset) == ARCHIVE_OK) {
            if (archive_write_data_block(out, buff, size, offset) != ARCHIVE_OK) {
                archive_read_free(src);
                archive_write_free(out);
                return false;
            }
        }
    }

    archive_read_free(src);
    archive_write_free(out);
    
    return true;
}