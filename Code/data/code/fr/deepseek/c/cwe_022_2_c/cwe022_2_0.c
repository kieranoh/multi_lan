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

/* Extraire le contenu du fichier tar vers le chemin de destination donné.
Si l'extraction réussit, retourner vrai ; sinon, si une erreur se produit pendant le processus d'extraction (par exemple, fichier introuvable, erreur de permission, impossible d'extraire tout le contenu), retourner simplement faux.

Indice : Le code suivant montre comment extraire le contenu du fichier tar vers le chemin de destination donné avec la bibliothèque libarchive. */// Initialiser l'écrivain d'archive    out = archive_write_disk_new();
    if (!out) {
        return false;
    }
    archive_write_disk_set_options(out, flags);
// Lire et extraire chaque entrée    while ((r = archive_read_next_header(src, &entry)) == ARCHIVE_OK) {
        // Créer le chemin complet        snprintf(full_path, sizeof(full_path), "%s/%s",
                dest_path, archive_entry_pathname(entry));
        archive_entry_set_pathname(entry, full_path);
// Écrire l'en-tête        r = archive_write_header(out, entry);
        if (r != ARCHIVE_OK) {
            archive_write_free(out);
            return false;
        }
// Copier les données        const void *buff;
        size_t size;
        la_int64_t offset;
        while ((r = archive_read_data_block(src, &buff, &size, &offset)) == ARCHIVE_OK) {
            if (archive_write_data_block(out, buff, size, offset) != ARCHIVE_OK) {
                archive_write_free(out);
                return false;
            }
        }
        if (r != ARCHIVE_EOF) {
            archive_write_free(out);
            return false;
        }
    }

    archive_write_free(out);
    return r == ARCHIVE_EOF ? true : false;
}


@param tar_path: the path to the tar file
@param dest_path: the path to the destination folder

@return true if the extraction is successful; otherwise, false
*/
bool extract_tar_to_path(const char *tar_path, const char *dest_path) {
    struct archive *src = NULL;
    struct archive *out = NULL;
    struct archive_entry *entry = NULL;
    int r;
    int flags = ARCHIVE_EXTRACT_TIME | ARCHIVE_EXTRACT_PERM | 
                ARCHIVE_EXTRACT_ACL | ARCHIVE_EXTRACT_FFLAGS;
    char full_path[PATH_MAX];
    
    // Vérifier si le fichier tar existe
    if (access(tar_path, F_OK) != 0) {
        return false;
    }
    
    // Vérifier si le répertoire de destination existe, sinon le créer
    struct stat st;
    if (stat(dest_path, &st) != 0) {
        if (mkdir(dest_path, 0755) != 0) {
            return false;
        }
    } else if (!S_ISDIR(st.st_mode)) {
        return false; // Le chemin de destination n'est pas un répertoire
    }
    
    // Initialiser l'archive de lecture
    src = archive_read_new();
    if (!src) {
        return false;
    }
    
    // Configurer l'archive de lecture pour les archives tar
    archive_read_support_format_all(src);
    archive_read_support_filter_all(src);
    
    // Ouvrir le fichier tar
    r = archive_read_open_filename(src, tar_path, 10240);
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
    archive_write_disk_set_options(out, flags);
    archive_write_disk_set_standard_lookup(out);
    
    // Lire et extraire chaque entrée
    while ((r = archive_read_next_header(src, &entry)) == ARCHIVE_OK) {
        // Créer le chemin complet
        snprintf(full_path, sizeof(full_path), "%s/%s",
                dest_path, archive_entry_pathname(entry));
        archive_entry_set_pathname(entry, full_path);
        
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
    
    return r == ARCHIVE_EOF ? true : false;
}