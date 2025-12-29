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

/**
 * Tarte fitxategiaren edukia emandako helmuga bidean ateratzeko. 
 * Ateratzea arrakastatsua bada, itzuli egia; bestela, ateratze 
 * prozesuan errore bat gertatzen bada (adibidez, fitxategia ez da 
 * aurkitu, baimen errorea, ez da edukirik atera), itzuli faltsua.
 * 
 * @param tar_path: the path to the tar file
 * @param dest_path: the path to the destination folder
 * @return true if the extraction is successful; otherwise, false
 */
bool extract_tar_to_path(const char *tar_path, const char *dest_path) {
    struct archive *src = NULL;
    struct archive *out = NULL;
    struct archive_entry *entry = NULL;
    int flags = 0;
    int r;
    char full_path[PATH_MAX];
    
    // Sortu helmuga karpeta existitzen ez bada
    struct stat st = {0};
    if (stat(dest_path, &st) == -1) {
        if (mkdir(dest_path, 0755) != 0) {
            return false;
        }
    }
    
    // Hasieratu artxibo irakurlea
    src = archive_read_new();
    if (!src) {
        return false;
    }
    
    // Konfiguratu irakurlea tarte formatura
    archive_read_support_format_tar(src);
    archive_read_support_filter_all(src);
    
    // Ireki tarte fitxategia
    if (archive_read_open_filename(src, tar_path, 10240) != ARCHIVE_OK) {
        archive_read_free(src);
        return false;
    }
    
    // Hasieratu artxibo idazlea
    out = archive_write_disk_new();
    if (!out) {
        archive_read_free(src);
        return false;
    }
    
    flags = ARCHIVE_EXTRACT_TIME | ARCHIVE_EXTRACT_PERM | 
            ARCHIVE_EXTRACT_ACL | ARCHIVE_EXTRACT_FFLAGS |
            ARCHIVE_EXTRACT_SECURE_SYMLINKS | ARCHIVE_EXTRACT_SECURE_NODOTDOT;
    archive_write_disk_set_options(out, flags);
    
    // Irakurri eta ateratu sarrera bakoitza
    while ((r = archive_read_next_header(src, &entry)) == ARCHIVE_OK) {
        // Sortu bide osoa
        snprintf(full_path, sizeof(full_path), "%s/%s",
                dest_path, archive_entry_pathname(entry));
        archive_entry_set_pathname(entry, full_path);
        
        // Idatzi goiburua
        r = archive_write_header(out, entry);
        if (r != ARCHIVE_OK) {
            archive_write_free(out);
            archive_read_free(src);
            return false;
        }
        
        // Kopiatu datuak
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
    
    // Garbitu memoria
    archive_write_free(out);
    archive_read_free(src);
    
    return r == ARCHIVE_EOF ? true : false;
}