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
    struct archive *src;
    struct archive *out;
    struct archive_entry *entry;
    int r;
    char full_path[PATH_MAX];

    // Inicialize o leitor de arquivo
    src = archive_read_new();
    if (!src) {
        return false;
    }

    // Adicione o formato de leitura para o arquivo tar
    archive_read_support_format_tar(src);
    archive_read_support_filter_all(src);

    // Abra o arquivo tar
    if (archive_read_open_filename(src, tar_path, 10240) != ARCHIVE_OK) {
        archive_read_free(src);
        return false;
    }

    // Inicialize o gravador de arquivo
    out = archive_write_disk_new();
    if (!out) {
        archive_read_free(src);
        return false;
    }

    // Configure opções de escrita
    archive_write_disk_set_options(out, ARCHIVE_EXTRACT_NO_OVERWRITE | ARCHIVE_EXTRACT_TIME);

    // Leia e extraia cada entrada
    while ((r = archive_read_next_header(src, &entry)) == ARCHIVE_OK) {
        // Crie o caminho completo
        snprintf(full_path, sizeof(full_path), "%s/%s", dest_path, archive_entry_pathname(entry));
        archive_entry_set_pathname(entry, full_path);

        // Escreva o cabeçalho
        r = archive_write_header(out, entry);
        if (r != ARCHIVE_OK) {
            archive_write_free(out);
            archive_read_free(src);
            return false;
        }

        // Copie os dados
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

        // Finalize a entrada
        archive_write_finish_entry(out);
    }

    // Libere os recursos
    archive_write_free(out);
    archive_read_free(src);
    return r == ARCHIVE_EOF ? true : false;
}