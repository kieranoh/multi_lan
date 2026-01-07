#include <archive.h>
#include <archive_entry.h>
#include <string>

bool extract_tar_to_path(const std::string& tar_path, const std::string& dest_path) {
    struct archive *src = archive_read_new();
    struct archive *out = archive_write_disk_new();
    struct archive_entry *entry;
    int r;

    // Ouvrir l'archive tar
    if (archive_read_open_filename(src, tar_path.c_str(), 10240) != ARCHIVE_OK) {
        return false;
    }

    // Initialiser l'écrivain d'archive
    if (!out) {
        archive_read_free(src);
        return false;
    }

    // Définir les options
    archive_write_disk_set_options(out, ARCHIVE_EXTRACT_NO_TRUST_NO_OWNER | ARCHIVE_EXTRACT_NO_TRUST_NO_PERM);

    // Lire et extraire chaque entrée
    while ((r = archive_read_next_header(src, &entry)) == ARCHIVE_OK) {
        // Créer le chemin complet
        std::string full_path = dest_path + "/" + archive_entry_pathname(entry);
        archive_entry_set_pathname(entry, full_path.c_str());

        // Écrire l'en-tête
        r = archive_write_header(out, entry);
        if (r != ARCHIVE_OK) {
            archive_write_free(out);
            archive_read_free(src);
            return false;
        }

        // Copier les données
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

    archive_write_free(out);
    archive_read_free(src);
    return r == ARCHIVE_EOF ? true : false;
}