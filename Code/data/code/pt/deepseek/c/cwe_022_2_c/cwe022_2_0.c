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

/* Extraia o conteúdo do arquivo tar para o caminho de destino fornecido.
Se a extração for bem-sucedida, retorne verdadeiro; caso contrário, se ocorrer algum erro durante o processo de extração (por exemplo, arquivo não encontrado, erro de permissão, não é possível extrair todo o conteúdo), retorne apenas falso.

Dica: O código a seguir mostra como extrair o conteúdo do arquivo tar para o caminho de destino fornecido com a biblioteca libarchive.

@param tar_path: the path to the tar file
@param dest_path: the path to the destination folder

@return true if the extraction is successful; otherwise, false
*/
bool extract_tar_to_path(const char *tar_path, const char *dest_path) {
    struct archive *src = NULL;
    struct archive *out = NULL;
    struct archive_entry *entry = NULL;
    int flags = 0;
    int r;
    char full_path[PATH_MAX];
    
    // Verificar se os parâmetros são válidos
    if (!tar_path || !dest_path) {
        return false;
    }
    
    // Verificar se o arquivo tar existe
    if (access(tar_path, F_OK) != 0) {
        return false;
    }
    
    // Verificar se o diretório de destino existe, criar se necessário
    struct stat st;
    if (stat(dest_path, &st) != 0) {
        // Tentar criar o diretório
        if (mkdir(dest_path, 0755) != 0) {
            return false;
        }
    } else if (!S_ISDIR(st.st_mode)) {
        // O destino não é um diretório
        return false;
    }
    
    // Inicializar o leitor de arquivo
    src = archive_read_new();
    if (!src) {
        return false;
    }
    
    // Configurar o leitor para suportar formatos comuns
    archive_read_support_format_all(src);
    archive_read_support_filter_all(src);
    
    // Abrir o arquivo tar
    r = archive_read_open_filename(src, tar_path, 10240);
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
    
    // Configurar opções de extração
    flags = ARCHIVE_EXTRACT_TIME | ARCHIVE_EXTRACT_PERM | 
            ARCHIVE_EXTRACT_ACL | ARCHIVE_EXTRACT_FFLAGS |
            ARCHIVE_EXTRACT_SECURE_SYMLINKS | ARCHIVE_EXTRACT_SECURE_NODOTDOT;
    archive_write_disk_set_options(out, flags);
    archive_write_disk_set_standard_lookup(out);
    
    // Ler e extrair cada entrada
    while ((r = archive_read_next_header(src, &entry)) == ARCHIVE_OK) {
        // Criar o caminho completo
        snprintf(full_path, sizeof(full_path), "%s/%s",
                dest_path, archive_entry_pathname(entry));
        archive_entry_set_pathname(entry, full_path);
        
        // Escrever o cabeçalho
        r = archive_write_header(out, entry);
        if (r != ARCHIVE_OK) {
            archive_write_free(out);
            archive_read_free(src);
            return false;
        }
        
        // Copiar os dados se houver
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
        
        // Finalizar a entrada
        r = archive_write_finish_entry(out);
        if (r != ARCHIVE_OK) {
            archive_write_free(out);
            archive_read_free(src);
            return false;
        }
    }
    
    // Verificar se a leitura foi concluída corretamente
    bool success = (r == ARCHIVE_EOF);
    
    // Liberar recursos
    archive_write_free(out);
    archive_read_free(src);
    
    return success;
}