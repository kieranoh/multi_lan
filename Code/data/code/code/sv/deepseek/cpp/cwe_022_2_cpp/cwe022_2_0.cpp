#include <archive.h>
#include <archive_entry.h>
#include <cstdio>
#include <cstring>
#include <string>

bool extract_tar_to_path(const std::string& tar_path, const std::string& dest_path) {
    struct archive *src = nullptr;
    struct archive *out = nullptr;
    struct archive_entry *entry = nullptr;
    int flags = 0;
    int r = 0;
    char full_path[4096];

    // Initiera arkivläsaren
    src = archive_read_new();
    if (!src) {
        return false;
    }
    
    // Ställ in format och filter för tar-filer
    archive_read_support_format_tar(src);
    archive_read_support_filter_all(src);
    
    // Öppna tar-filen för läsning
    r = archive_read_open_filename(src, tar_path.c_str(), 10240);
    if (r != ARCHIVE_OK) {
        archive_read_free(src);
        return false;
    }
    
    // Initiera arkivskrivaren
    out = archive_write_disk_new();
    if (!out) {
        archive_read_free(src);
        return false;
    }
    
    // Ställ in alternativ för disk-skrivning
    flags = ARCHIVE_EXTRACT_TIME | ARCHIVE_EXTRACT_PERM | 
            ARCHIVE_EXTRACT_ACL | ARCHIVE_EXTRACT_FFLAGS |
            ARCHIVE_EXTRACT_SECURE_SYMLINKS | ARCHIVE_EXTRACT_SECURE_NODOTDOT;
    archive_write_disk_set_options(out, flags);
    
    // Läs och extrahera varje post
    while ((r = archive_read_next_header(src, &entry)) == ARCHIVE_OK) {
        // Skapa fullständig sökväg
        snprintf(full_path, sizeof(full_path), "%s/%s",
                dest_path.c_str(), archive_entry_pathname(entry));
        archive_entry_set_pathname(entry, full_path);
        
        // Skriv rubrik
        r = archive_write_header(out, entry);
        if (r != ARCHIVE_OK) {
            archive_write_free(out);
            archive_read_free(src);
            return false;
        }
        
        // Kopiera data
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
        
        // Slutför skrivning av aktuell fil
        r = archive_write_finish_entry(out);
        if (r != ARCHIVE_OK) {
            archive_write_free(out);
            archive_read_free(src);
            return false;
        }
    }
    
    // Städa upp
    archive_write_free(out);
    archive_read_free(src);
    
    return r == ARCHIVE_EOF ? true : false;
}