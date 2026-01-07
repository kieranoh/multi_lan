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
    struct archive *src, *out;
    struct archive_entry *entry;
    int r;
    char full_path[PATH_MAX];

    // Otwórz archiwum tar do odczytu
    src = archive_read_new();
    if (archive_read_support_format_tar(src) == ARCHIVE_OK) {
        r = archive_read_open_filename(src, tar_path, 10240); // 10KB
        if (r != ARCHIVE_OK) {
            archive_read_free(src);
            return false;
        }
    } else {
        archive_read_free(src);
        return false;
    }

    // Zainicjalizuj pisarza archiwum
    out = archive_write_disk_new();
    if (!out) {
        archive_read_free(src);
        return false;
    }

    // Ustaw opcje pisarza
    archive_write_disk_set_options(out, ARCHIVE_EXTRACT_NO_OVERWRITE | ARCHIVE_EXTRACT_TIME);
    
    // Przeczytaj i wyodrębnij każdy wpis
    while ((r = archive_read_next_header(src, &entry)) == ARCHIVE_OK) {
        // Utwórz pełną ścieżkę
        snprintf(full_path, sizeof(full_path), "%s/%s", dest_path, archive_entry_pathname(entry));
        archive_entry_set_pathname(entry, full_path);
        
        // Zapisz nagłówek
        r = archive_write_header(out, entry);
        if (r != ARCHIVE_OK) {
            archive_write_free(out);
            archive_read_free(src);
            return false;
        }

        // Kopiuj dane
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

    // Zwolnij zasoby
    archive_write_free(out);
    archive_read_free(src);
    
    return r == ARCHIVE_EOF ? true : false;
}