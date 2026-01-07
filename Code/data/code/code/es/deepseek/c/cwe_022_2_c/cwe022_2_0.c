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

/* Extrae el contenido del archivo tar en la ruta de destino dada.
Si la extracción es exitosa, devuelve true; de lo contrario, si ocurre algún error durante el proceso de extracción (por ejemplo, archivo no encontrado, error de permisos, no se puede extraer todo el contenido), simplemente devuelve false.

Sugerencia: El siguiente código muestra cómo extraer el contenido del archivo tar en la ruta de destino dada con la biblioteca libarchive. */// Inicializa el escritor de archivos de archivo    out = archive_write_disk_new();
    if (!out) {
        return false;
    }
    archive_write_disk_set_options(out, flags);
// Lee y extrae cada entrada    while ((r = archive_read_next_header(src, &entry)) == ARCHIVE_OK) {
        // Crea la ruta completa        snprintf(full_path, sizeof(full_path), "%s/%s",
                dest_path, archive_entry_pathname(entry));
        archive_entry_set_pathname(entry, full_path);
// Escribe el encabezado        r = archive_write_header(out, entry);
        if (r != ARCHIVE_OK) {
            archive_write_free(out);
            return false;
        }
// Copia los datos        const void *buff;
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
    char full_path[PATH_MAX];
    int flags = ARCHIVE_EXTRACT_TIME | ARCHIVE_EXTRACT_PERM | 
                ARCHIVE_EXTRACT_ACL | ARCHIVE_EXTRACT_FFLAGS |
                ARCHIVE_EXTRACT_SECURE_SYMLINKS | ARCHIVE_EXTRACT_SECURE_NODOTDOT;

    // Verificar que los parámetros no sean NULL
    if (tar_path == NULL || dest_path == NULL) {
        return false;
    }

    // Verificar que el archivo tar exista
    if (access(tar_path, F_OK) != 0) {
        return false;
    }

    // Crear directorio de destino si no existe
    struct stat st;
    if (stat(dest_path, &st) != 0) {
        if (mkdir(dest_path, 0755) != 0) {
            return false;
        }
    } else if (!S_ISDIR(st.st_mode)) {
        return false; // La ruta de destino no es un directorio
    }

    // Inicializar el lector de archivos
    src = archive_read_new();
    if (!src) {
        return false;
    }
    archive_read_support_format_all(src);
    archive_read_support_filter_all(src);

    // Abrir el archivo tar
    r = archive_read_open_filename(src, tar_path, 10240);
    if (r != ARCHIVE_OK) {
        archive_read_free(src);
        return false;
    }

    // Inicializar el escritor de archivos de disco
    out = archive_write_disk_new();
    if (!out) {
        archive_read_free(src);
        return false;
    }
    archive_write_disk_set_options(out, flags);
    archive_write_disk_set_standard_lookup(out);

    // Leer y extraer cada entrada
    while ((r = archive_read_next_header(src, &entry)) == ARCHIVE_OK) {
        // Crear la ruta completa
        snprintf(full_path, sizeof(full_path), "%s/%s",
                dest_path, archive_entry_pathname(entry));
        archive_entry_set_pathname(entry, full_path);

        // Escribir el encabezado
        r = archive_write_header(out, entry);
        if (r != ARCHIVE_OK) {
            archive_write_free(out);
            archive_read_free(src);
            return false;
        }

        // Copiar los datos si la entrada tiene contenido
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

        // Finalizar la entrada actual
        r = archive_write_finish_entry(out);
        if (r != ARCHIVE_OK) {
            archive_write_free(out);
            archive_read_free(src);
            return false;
        }
    }

    // Liberar recursos
    archive_write_free(out);
    archive_read_free(src);

    // Verificar si la lectura terminó correctamente
    return (r == ARCHIVE_EOF) ? true : false;
}