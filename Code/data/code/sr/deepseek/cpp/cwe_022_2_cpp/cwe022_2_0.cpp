#include <archive.h>
#include <archive_entry.h>
#include <cstring>
#include <string>
#include <sys/stat.h>
#include <sys/types.h>

bool extract_tar_to_path(const std::string& tar_path, const std::string& dest_path) {
    struct archive *src = nullptr;
    struct archive *out = nullptr;
    struct archive_entry *entry = nullptr;
    int flags = 0;
    int r = 0;
    
    // Kreirajte odredišnu fasciklu ako ne postoji
    struct stat st;
    if (stat(dest_path.c_str(), &st) != 0) {
        // Pokušajte da kreirate fasciklu
        if (mkdir(dest_path.c_str(), 0755) != 0) {
            return false;
        }
    }
    
    // Inicijalizujte čitač arhive
    src = archive_read_new();
    if (!src) {
        return false;
    }
    
    // Podržite različite formate arhiva
    archive_read_support_format_all(src);
    archive_read_support_filter_all(src);
    
    // Otvorite tar datoteku
    r = archive_read_open_filename(src, tar_path.c_str(), 10240);
    if (r != ARCHIVE_OK) {
        archive_read_free(src);
        return false;
    }
    
    // Inicijalizujte pisca arhive
    out = archive_write_disk_new();
    if (!out) {
        archive_read_free(src);
        return false;
    }
    
    // Postavite opcije za pisanje na disk
    flags = ARCHIVE_EXTRACT_TIME | ARCHIVE_EXTRACT_PERM | 
            ARCHIVE_EXTRACT_ACL | ARCHIVE_EXTRACT_FFLAGS |
            ARCHIVE_EXTRACT_SECURE_SYMLINKS | ARCHIVE_EXTRACT_SECURE_NODOTDOT;
    archive_write_disk_set_options(out, flags);
    
    // Postavite standardne dozvole
    archive_write_disk_set_standard_lookup(out);
    
    // Pročitajte i izvucite svaki unos
    while ((r = archive_read_next_header(src, &entry)) == ARCHIVE_OK) {
        // Kreirajte punu putanju
        std::string full_path = dest_path + "/" + archive_entry_pathname(entry);
        archive_entry_set_pathname(entry, full_path.c_str());
        
        // Zapišite zaglavlje
        r = archive_write_header(out, entry);
        if (r != ARCHIVE_OK) {
            archive_write_free(out);
            archive_read_free(src);
            return false;
        }
        
        // Kopirajte podatke
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
        
        // Završite unos
        r = archive_write_finish_entry(out);
        if (r != ARCHIVE_OK) {
            archive_write_free(out);
            archive_read_free(src);
            return false;
        }
    }
    
    // Oslobodite resurse
    archive_write_free(out);
    archive_read_free(src);
    
    // Proverite da li je čitanje završeno uspešno
    return (r == ARCHIVE_EOF) ? true : false;
}