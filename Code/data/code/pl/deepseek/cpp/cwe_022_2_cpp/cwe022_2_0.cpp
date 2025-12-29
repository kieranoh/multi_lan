#include <archive.h>
#include <archive_entry.h>
#include <string>
#include <cstring>
#include <cstdio>

bool extract_tar_to_path(const std::string& tar_path, const std::string& dest_path) {
    struct archive *src = nullptr;
    struct archive *out = nullptr;
    struct archive_entry *entry = nullptr;
    int flags = ARCHIVE_EXTRACT_TIME | ARCHIVE_EXTRACT_PERM | ARCHIVE_EXTRACT_ACL | ARCHIVE_EXTRACT_FFLAGS;
    int r = 0;
    char full_path[4096];

    // Inicjalizuj czytnik archiwum
    src = archive_read_new();
    if (!src) {
        return false;
    }
    archive_read_support_format_tar(src);
    archive_read_support_filter_all(src);

    // Otwórz plik tar
    if (archive_read_open_filename(src, tar_path.c_str(), 10240) != ARCHIVE_OK) {
        archive_read_free(src);
        return false;
    }

    // Inicjalizuj pisarza dysku
    out = archive_write_disk_new();
    if (!out) {
        archive_read_free(src);
        return false;
    }
    archive_write_disk_set_options(out, flags);
    archive_write_disk_set_standard_lookup(out);

    // Odczytaj i wyodrębnij każdy wpis
    while ((r = archive_read_next_header(src, &entry)) == ARCHIVE_OK) {
        // Utwórz pełną ścieżkę
        snprintf(full_path, sizeof(full_path), "%s/%s",
                dest_path.c_str(), archive_entry_pathname(entry));
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

    // Sprawdź czy odczyt zakończył się poprawnie
    return (r == ARCHIVE_EOF);
}