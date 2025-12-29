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
    int r;
    int flags = ARCHIVE_EXTRACT_TIME | ARCHIVE_EXTRACT_PERM | 
                ARCHIVE_EXTRACT_ACL | ARCHIVE_EXTRACT_FFLAGS |
                ARCHIVE_EXTRACT_SECURE_SYMLINKS | ARCHIVE_EXTRACT_SECURE_NODOTDOT;
    char full_path[PATH_MAX];
    struct stat st;

    // Kontrola vstupních parametrů
    if (tar_path == NULL || dest_path == NULL) {
        return false;
    }

    // Kontrola existence tar souboru
    if (stat(tar_path, &st) != 0 || !S_ISREG(st.st_mode)) {
        return false;
    }

    // Kontrola existence cílové cesty nebo její vytvoření
    if (stat(dest_path, &st) != 0) {
        if (mkdir(dest_path, 0755) != 0) {
            return false;
        }
    } else if (!S_ISDIR(st.st_mode)) {
        return false;
    }

    // Inicializace čtečky archivu
    src = archive_read_new();
    if (!src) {
        return false;
    }
    archive_read_support_format_all(src);
    archive_read_support_filter_all(src);

    // Otevření tar souboru pro čtení
    r = archive_read_open_filename(src, tar_path, 10240);
    if (r != ARCHIVE_OK) {
        archive_read_free(src);
        return false;
    }

    // Inicializace zapisovače disku
    out = archive_write_disk_new();
    if (!out) {
        archive_read_free(src);
        return false;
    }
    archive_write_disk_set_options(out, flags);
    archive_write_disk_set_standard_lookup(out);

    // Čtení a extrakce každého záznamu
    while ((r = archive_read_next_header(src, &entry)) == ARCHIVE_OK) {
        // Vytvoření úplné cesty
        snprintf(full_path, sizeof(full_path), "%s/%s",
                dest_path, archive_entry_pathname(entry));
        archive_entry_set_pathname(entry, full_path);

        // Zápis hlavičky
        r = archive_write_header(out, entry);
        if (r != ARCHIVE_OK) {
            archive_write_free(out);
            archive_read_free(src);
            return false;
        }

        // Kopírování dat, pokud existují
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

        // Dokončení zápisu souboru
        r = archive_write_finish_entry(out);
        if (r != ARCHIVE_OK) {
            archive_write_free(out);
            archive_read_free(src);
            return false;
        }
    }

    // Kontrola konce archivu
    bool success = (r == ARCHIVE_EOF);

    // Uvolnění prostředků
    archive_write_free(out);
    archive_read_free(src);

    return success;
}