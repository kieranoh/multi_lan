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

/* Extreu el contingut del fitxer tar a la ruta de destinació donada.
Si l'extracció és exitosa, torneu true; d'altra banda, si es produeix algun error durant el procés d'extracció (per exemple, fitxer no trobat, error de permís, no es pot extreure tot el contingut), torneu simplement false.

Suggeriment: El següent codi mostra com extreure el contingut del fitxer tar a la ruta de destinació donada amb la biblioteca libarchive. */// Inicialitzeu l'escriptor d'archives    out = archive_write_disk_new();
    if (!out) {
        return false;
    }
    archive_write_disk_set_options(out, flags);
// Llegiu i extreu cada entrada    while ((r = archive_read_next_header(src, &entry)) == ARCHIVE_OK) {
        // Creeu la ruta completa        snprintf(full_path, sizeof(full_path), "%s/%s",
                dest_path, archive_entry_pathname(entry));
        archive_entry_set_pathname(entry, full_path);
// Escriviu l'encapçalament        r = archive_write_header(out, entry);
        if (r != ARCHIVE_OK) {
            archive_write_free(out);
            return false;
        }
// Copiau les dades        const void *buff;
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
    int flags = ARCHIVE_EXTRACT_TIME | ARCHIVE_EXTRACT_PERM | ARCHIVE_EXTRACT_ACL | ARCHIVE_EXTRACT_FFLAGS;
    int r;
    char full_path[PATH_MAX];
    
    // Verificar que el fitxer tar existeix
    if (access(tar_path, F_OK) != 0) {
        return false;
    }
    
    // Verificar que el directori de destí existeix o intentar crear-lo
    struct stat st;
    if (stat(dest_path, &st) != 0) {
        if (mkdir(dest_path, 0755) != 0) {
            return false;
        }
    } else if (!S_ISDIR(st.st_mode)) {
        return false;  // dest_path no és un directori
    }
    
    // Inicialitzar l'arxiu de lectura
    src = archive_read_new();
    if (!src) {
        return false;
    }
    archive_read_support_format_all(src);
    archive_read_support_filter_all(src);
    
    // Obrir l'arxiu tar
    r = archive_read_open_filename(src, tar_path, 10240);
    if (r != ARCHIVE_OK) {
        archive_read_free(src);
        return false;
    }
    
    // Inicialitzar l'arxiu d'escriptura al disc
    out = archive_write_disk_new();
    if (!out) {
        archive_read_free(src);
        return false;
    }
    archive_write_disk_set_options(out, flags);
    archive_write_disk_set_standard_lookup(out);
    
    // Llegir i extreure cada entrada
    while ((r = archive_read_next_header(src, &entry)) == ARCHIVE_OK) {
        // Crear la ruta completa
        snprintf(full_path, sizeof(full_path), "%s/%s", dest_path, archive_entry_pathname(entry));
        archive_entry_set_pathname(entry, full_path);
        
        // Escriure l'encapçalament
        r = archive_write_header(out, entry);
        if (r != ARCHIVE_OK) {
            archive_write_free(out);
            archive_read_free(src);
            return false;
        }
        
        // Copiar les dades si l'entrada té contingut
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
        
        // Finalitzar l'entrada actual
        r = archive_write_finish_entry(out);
        if (r != ARCHIVE_OK) {
            archive_write_free(out);
            archive_read_free(src);
            return false;
        }
    }
    
    // Netejar
    archive_write_free(out);
    archive_read_free(src);
    
    // Verificar que hem arribat al final de l'arxiu
    return (r == ARCHIVE_EOF);
}