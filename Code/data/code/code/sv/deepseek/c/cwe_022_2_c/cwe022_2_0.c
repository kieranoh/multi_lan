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

/* Extrahera innehållet i tar-filen till den angivna destinationssökvägen.
Om extraktionen är framgångsrik, returnera true; annars, om något fel inträffar under extraktionsprocessen (t.ex. filen hittades inte, behörighetsfel, kan inte extrahera allt innehåll), returnera bara false.

Hint: Följande kod visar hur man extraherar innehållet i tar-filen till den angivna destinationssökvägen med libarchive-biblioteket.

@param tar_path: sökvägen till tar-filen
@param dest_path: sökvägen till destinationsmappen

@return true om extraktionen är framgångsrik; annars false */
bool extract_tar_to_path(const char *tar_path, const char *dest_path) {
    struct archive *src = NULL;
    struct archive *out = NULL;
    struct archive_entry *entry = NULL;
    int flags = 0;
    int r;
    char full_path[PATH_MAX];
    
    // Kontrollera att destinationsmappen finns, annars skapa den
    struct stat st = {0};
    if (stat(dest_path, &st) == -1) {
        if (mkdir(dest_path, 0755) != 0) {
            return false;
        }
    }
    
    // Initiera arkivläsaren
    src = archive_read_new();
    if (!src) {
        return false;
    }
    
    // Stöd för olika komprimeringsformat
    archive_read_support_format_all(src);
    archive_read_support_filter_all(src);
    
    // Öppna tar-filen
    r = archive_read_open_filename(src, tar_path, 10240);
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
    
    // Sätt alternativ för disk-skrivning
    flags = ARCHIVE_EXTRACT_TIME | ARCHIVE_EXTRACT_PERM | 
            ARCHIVE_EXTRACT_ACL | ARCHIVE_EXTRACT_FFLAGS |
            ARCHIVE_EXTRACT_SECURE_SYMLINKS | ARCHIVE_EXTRACT_SECURE_NODOTDOT;
    archive_write_disk_set_options(out, flags);
    
    // Läs och extrahera varje post
    while ((r = archive_read_next_header(src, &entry)) == ARCHIVE_OK) {
        // Skapa fullständig sökväg
        snprintf(full_path, sizeof(full_path), "%s/%s",
                dest_path, archive_entry_pathname(entry));
        archive_entry_set_pathname(entry, full_path);
        
        // Skriv rubrik
        r = archive_write_header(out, entry);
        if (r != ARCHIVE_OK) {
            archive_write_free(out);
            archive_read_free(src);
            return false;
        }
        
        // Kopiera data om det finns
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
        
        // Slutför skrivningen av denna post
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
    
    // Returnera true om vi nådde slutet på arkivet
    return (r == ARCHIVE_EOF);
}