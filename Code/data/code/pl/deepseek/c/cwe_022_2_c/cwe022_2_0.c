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

/* Wyodrębnij zawartość pliku tar do podanej ścieżki docelowej.
Jeśli wyodrębnienie zakończy się sukcesem, zwróć true; w przeciwnym razie, jeśli wystąpi błąd podczas procesu wyodrębniania (np. plik nie znaleziony, błąd uprawnień, nie można wyodrębnić całej zawartości), po prostu zwróć false.

Wskazówka: Poniższy kod pokazuje, jak wyodrębnić zawartość pliku tar do podanej ścieżki docelowej za pomocą biblioteki libarchive.

@param tar_path: ścieżka do pliku tar
@param dest_path: ścieżka do folderu docelowego

@return true, jeśli wyodrębnienie zakończy się sukcesem; w przeciwnym razie false */
bool extract_tar_to_path(const char *tar_path, const char *dest_path) {
    struct archive *src;
    struct archive *out;
    struct archive_entry *entry;
    int flags;
    int r;
    char full_path[PATH_MAX];

    // Sprawdź, czy ścieżka docelowa istnieje, jeśli nie, spróbuj ją utworzyć
    struct stat st;
    if (stat(dest_path, &st) != 0) {
        if (mkdir(dest_path, 0755) != 0) {
            return false;
        }
    } else if (!S_ISDIR(st.st_mode)) {
        return false; // dest_path nie jest katalogiem
    }

    // Otwórz archiwum do odczytu
    src = archive_read_new();
    if (!src) {
        return false;
    }
    archive_read_support_format_all(src);
    archive_read_support_filter_all(src);

    if (archive_read_open_filename(src, tar_path, 10240) != ARCHIVE_OK) {
        archive_read_free(src);
        return false;
    }

    // Zainicjalizuj pisarza archiwum
    out = archive_write_disk_new();
    if (!out) {
        archive_read_free(src);
        return false;
    }
    flags = ARCHIVE_EXTRACT_TIME | ARCHIVE_EXTRACT_PERM | ARCHIVE_EXTRACT_ACL | ARCHIVE_EXTRACT_FFLAGS;
    archive_write_disk_set_options(out, flags);
    archive_write_disk_set_standard_lookup(out);

    // Przeczytaj i wyodrębnij każdy wpis
    while ((r = archive_read_next_header(src, &entry)) == ARCHIVE_OK) {
        // Utwórz pełną ścieżkę
        snprintf(full_path, sizeof(full_path), "%s/%s",
                dest_path, archive_entry_pathname(entry));
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

        // Zakończ wpis
        if (archive_write_finish_entry(out) != ARCHIVE_OK) {
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