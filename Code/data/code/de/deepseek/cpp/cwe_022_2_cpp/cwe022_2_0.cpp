#include <archive.h>
#include <archive_entry.h>
#include <string>
#include <cstring>
#include <memory>

bool extract_tar_to_path(const std::string& tar_path, const std::string& dest_path) {
    struct archive* src = archive_read_new();
    struct archive* out = archive_write_disk_new();
    
    if (!src || !out) {
        if (src) archive_read_free(src);
        if (out) archive_write_free(out);
        return false;
    }
    
    // Konfiguriere das Quellarchiv für TAR-Dateien
    archive_read_support_format_tar(src);
    archive_read_support_filter_all(src);
    
    // Konfiguriere den Disk-Writer
    int flags = ARCHIVE_EXTRACT_TIME | ARCHIVE_EXTRACT_PERM | 
                ARCHIVE_EXTRACT_ACL | ARCHIVE_EXTRACT_FFLAGS |
                ARCHIVE_EXTRACT_SECURE_SYMLINKS | ARCHIVE_EXTRACT_SECURE_NODOTDOT;
    archive_write_disk_set_options(out, flags);
    archive_write_disk_set_standard_lookup(out);
    
    // Öffne die TAR-Datei
    if (archive_read_open_filename(src, tar_path.c_str(), 10240) != ARCHIVE_OK) {
        archive_read_free(src);
        archive_write_free(out);
        return false;
    }
    
    bool success = true;
    struct archive_entry* entry;
    
    // Lese und extrahiere jeden Eintrag
    while (true) {
        int r = archive_read_next_header(src, &entry);
        
        if (r == ARCHIVE_EOF) {
            break;
        }
        
        if (r != ARCHIVE_OK) {
            success = false;
            break;
        }
        
        // Erstelle den vollständigen Pfad
        std::string full_path = dest_path + "/" + archive_entry_pathname(entry);
        archive_entry_set_pathname(entry, full_path.c_str());
        
        // Schreibe Header
        r = archive_write_header(out, entry);
        if (r != ARCHIVE_OK) {
            success = false;
            break;
        }
        
        // Kopiere Daten, falls vorhanden
        if (archive_entry_size(entry) > 0) {
            const void* buff;
            size_t size;
            la_int64_t offset;
            
            while (true) {
                r = archive_read_data_block(src, &buff, &size, &offset);
                if (r == ARCHIVE_EOF) {
                    break;
                }
                if (r != ARCHIVE_OK) {
                    success = false;
                    break;
                }
                
                if (archive_write_data_block(out, buff, size, offset) != ARCHIVE_OK) {
                    success = false;
                    break;
                }
            }
            
            if (!success) {
                break;
            }
        }
        
        // Finalisiere den Eintrag
        if (archive_write_finish_entry(out) != ARCHIVE_OK) {
            success = false;
            break;
        }
    }
    
    // Aufräumen
    archive_read_close(src);
    archive_read_free(src);
    archive_write_close(out);
    archive_write_free(out);
    
    return success;
}