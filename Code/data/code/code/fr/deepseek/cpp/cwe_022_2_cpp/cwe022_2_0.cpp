#include <archive.h>
#include <archive_entry.h>
#include <string>
#include <cstring>
#include <cstdio>

bool extract_tar_to_path(const std::string& tar_path, const std::string& dest_path) {
    struct archive *src = nullptr;
    struct archive *out = nullptr;
    struct archive_entry *entry = nullptr;
    int flags = 0;
    int r;
    char full_path[4096];

    // Initialiser l'archive de lecture
    src = archive_read_new();
    if (!src) {
        return false;
    }
    
    // Configurer l'archive de lecture pour le format tar
    archive_read_support_format_tar(src);
    archive_read_support_filter_all(src);
    
    // Ouvrir le fichier tar
    r = archive_read_open_filename(src, tar_path.c_str(), 10240);
    if (r != ARCHIVE_OK) {
        archive_read_free(src);
        return false;
    }

    // Initialiser l'écrivain d'archive
    out = archive_write_disk_new();
    if (!out) {
        archive_read_free(src);
        return false;
    }
    
    // Configurer les options d'écriture
    flags = ARCHIVE_EXTRACT_TIME | ARCHIVE_EXTRACT_PERM | ARCHIVE_EXTRACT_ACL | 
            ARCHIVE_EXTRACT_FFLAGS | ARCHIVE_EXTRACT_SECURE_SYMLINKS |
            ARCHIVE_EXTRACT_SECURE_NODOTDOT;
    archive_write_disk_set_options(out, flags);
    archive_write_disk_set_standard_lookup(out);

    // Lire et extraire chaque entrée
    while ((r = archive_read_next_header(src, &entry)) == ARCHIVE_OK) {
        // Créer le chemin complet
        snprintf(full_path, sizeof(full_path), "%s/%s",
                dest_path.c_str(), archive_entry_pathname(entry));
        archive_entry_set_pathname(entry, full_path);
        
        // Écrire l'en-tête
        r = archive_write_header(out, entry);
        if (r != ARCHIVE_OK) {
            archive_write_free(out);
            archive_read_free(src);
            return false;
        }
        
        // Copier les données si l'entrée a un contenu
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
        
        // Finaliser l'entrée
        r = archive_write_finish_entry(out);
        if (r != ARCHIVE_OK) {
            archive_write_free(out);
            archive_read_free(src);
            return false;
        }
    }

    // Nettoyer
    archive_write_free(out);
    archive_read_free(src);
    
    // Vérifier si la lecture s'est terminée correctement
    return (r == ARCHIVE_EOF);
}