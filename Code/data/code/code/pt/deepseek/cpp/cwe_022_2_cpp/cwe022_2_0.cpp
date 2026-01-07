#include <archive.h>
#include <archive_entry.h>
#include <cstdio>
#include <string>
#include <cstring>

/**
 * Extraia o conteúdo do arquivo tar para o caminho de destino fornecido.
 * Se a extração for bem-sucedida, retorne verdadeiro; caso contrário, se ocorrer algum erro durante o processo de extração (por exemplo, arquivo não encontrado, erro de permissão, não é possível extrair todo o conteúdo), retorne apenas falso.
 * 
 * @param tar_path: the path to the tar file
 * @param dest_path: the path to the destination folder
 * @return true if the extraction is successful; otherwise, false
 */
bool extract_tar_to_path(const std::string& tar_path, const std::string& dest_path) {
    struct archive *src = nullptr;
    struct archive *out = nullptr;
    struct archive_entry *entry = nullptr;
    int flags = ARCHIVE_EXTRACT_TIME | ARCHIVE_EXTRACT_PERM | ARCHIVE_EXTRACT_ACL | ARCHIVE_EXTRACT_FFLAGS;
    int r;
    char full_path[4096];

    // Inicializar o leitor de arquivo
    src = archive_read_new();
    if (!src) {
        return false;
    }
    archive_read_support_format_all(src);
    archive_read_support_filter_all(src);

    // Abrir o arquivo tar
    r = archive_read_open_filename(src, tar_path.c_str(), 10240);
    if (r != ARCHIVE_OK) {
        archive_read_free(src);
        return false;
    }

    // Inicializar o gravador de arquivo
    out = archive_write_disk_new();
    if (!out) {
        archive_read_free(src);
        return false;
    }
    archive_write_disk_set_options(out, flags);
    archive_write_disk_set_standard_lookup(out);

    // Ler e extrair cada entrada
    while ((r = archive_read_next_header(src, &entry)) == ARCHIVE_OK) {
        // Criar o caminho completo
        snprintf(full_path, sizeof(full_path), "%s/%s",
                dest_path.c_str(), archive_entry_pathname(entry));
        archive_entry_set_pathname(entry, full_path);

        // Escrever o cabeçalho
        r = archive_write_header(out, entry);
        if (r != ARCHIVE_OK) {
            archive_write_free(out);
            archive_read_free(src);
            return false;
        }

        // Copiar os dados
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

        // Finalizar a entrada
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

    // Verificar se a leitura terminou corretamente
    return (r == ARCHIVE_EOF);
}