#include <archive.h>
#include <archive_entry.h>
#include <cstring>
#include <string>

bool extract_tar_to_path(const std::string& tar_path, const std::string& dest_path) {
    struct archive *src = nullptr;
    struct archive *out = nullptr;
    struct archive_entry *entry = nullptr;
    int flags = 0;
    int r = 0;
    char full_path[4096];

    // Inicialitzem l'arxiu de lectura
    src = archive_read_new();
    if (!src) {
        return false;
    }
    archive_read_support_format_all(src);
    archive_read_support_filter_all(src);

    // Obrim l'arxiu tar
    r = archive_read_open_filename(src, tar_path.c_str(), 10240);
    if (r != ARCHIVE_OK) {
        archive_read_free(src);
        return false;
    }

    // Inicialitzem l'escriptor d'arxius de disc
    out = archive_write_disk_new();
    if (!out) {
        archive_read_free(src);
        return false;
    }
    flags = ARCHIVE_EXTRACT_TIME | ARCHIVE_EXTRACT_PERM | ARCHIVE_EXTRACT_ACL | ARCHIVE_EXTRACT_FFLAGS;
    archive_write_disk_set_options(out, flags);

    // Llegim i extraiem cada entrada
    while ((r = archive_read_next_header(src, &entry)) == ARCHIVE_OK) {
        // Creem la ruta completa
        snprintf(full_path, sizeof(full_path), "%s/%s",
                dest_path.c_str(), archive_entry_pathname(entry));
        archive_entry_set_pathname(entry, full_path);

        // Escrivim l'encapçalament
        r = archive_write_header(out, entry);
        if (r != ARCHIVE_OK) {
            archive_write_free(out);
            archive_read_free(src);
            return false;
        }

        // Copiem les dades
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

    // Alliberem recursos
    archive_write_free(out);
    archive_read_free(src);

    return r == ARCHIVE_EOF ? true : false;
}