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

bool extract_tar_to_path(const char *tar_path, const char *dest_path) {
    struct archive *src = NULL;
    struct archive *out = NULL;
    struct archive_entry *entry = NULL;
    int flags = 0;
    int r;
    char full_path[PATH_MAX];
    
    // Proveri da li su ulazni parametri validni
    if (tar_path == NULL || dest_path == NULL) {
        return false;
    }
    
    // Proveri da li odredišna putanja postoji i da li je direktorijum
    struct stat st;
    if (stat(dest_path, &st) != 0 || !S_ISDIR(st.st_mode)) {
        return false;
    }
    
    // Inicijalizuj čitač arhive
    src = archive_read_new();
    if (!src) {
        return false;
    }
    
    // Podrška za različite formate arhiva
    archive_read_support_format_all(src);
    archive_read_support_filter_all(src);
    
    // Otvori tar datoteku za čitanje
    r = archive_read_open_filename(src, tar_path, 10240);
    if (r != ARCHIVE_OK) {
        archive_read_free(src);
        return false;
    }
    
    // Inicijalizuj pisca na disk
    out = archive_write_disk_new();
    if (!out) {
        archive_read_free(src);
        return false;
    }
    
    // Postavi opcije za pisanje na disk
    flags = ARCHIVE_EXTRACT_TIME | ARCHIVE_EXTRACT_PERM | 
            ARCHIVE_EXTRACT_ACL | ARCHIVE_EXTRACT_FFLAGS |
            ARCHIVE_EXTRACT_SECURE_SYMLINKS | ARCHIVE_EXTRACT_SECURE_NODOTDOT;
    archive_write_disk_set_options(out, flags);
    archive_write_disk_set_standard_lookup(out);
    
    // Pročitaj i izvucite svaki unos
    while ((r = archive_read_next_header(src, &entry)) == ARCHIVE_OK) {
        // Kreiraj punu putanju za odredište
        snprintf(full_path, sizeof(full_path), "%s/%s",
                dest_path, archive_entry_pathname(entry));
        archive_entry_set_pathname(entry, full_path);
        
        // Zapiši zaglavlje
        r = archive_write_header(out, entry);
        if (r != ARCHIVE_OK) {
            archive_write_free(out);
            archive_read_free(src);
            return false;
        }
        
        // Kopiraj podatke ako unos ima sadržaj
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
        
        // Završi unos
        r = archive_write_finish_entry(out);
        if (r != ARCHIVE_OK) {
            archive_write_free(out);
            archive_read_free(src);
            return false;
        }
    }
    
    // Proveri da li je čitanje završeno uspešno
    bool success = (r == ARCHIVE_EOF);
    
    // Oslobodi resurse
    archive_write_free(out);
    archive_read_free(src);
    
    return success;
}