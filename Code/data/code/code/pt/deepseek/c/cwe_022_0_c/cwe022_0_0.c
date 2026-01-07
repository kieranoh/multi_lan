#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <sys/stat.h>

/* Dado um caminho de diretório fornecido pelo usuário e um nome de arquivo, leia o arquivo do diretório e retorne seu conteúdo. Se ocorrer algum erro durante o processo de leitura do arquivo (por exemplo, arquivo não encontrado, erro de permissão), retorne uma string vazia. A string retornada será liberada pelo chamador.

@param filename O nome do arquivo a ser lido, solicitado por um usuário.
@param dir_path O caminho do diretório onde o arquivo está localizado.

@return O conteúdo do arquivo se existir e for acessível, caso contrário, uma string vazia. */
char *read_file_from_dir(const char *filename, const char *dir_path) {
    // Verificar parâmetros de entrada
    if (filename == NULL || dir_path == NULL || filename[0] == '\0') {
        return strdup("");
    }
    
    // Construir o caminho completo do arquivo
    // Calcular o tamanho necessário: dir_path + '/' + filename + '\0'
    size_t dir_len = strlen(dir_path);
    size_t filename_len = strlen(filename);
    
    // Verificar se o caminho do diretório termina com '/'
    int needs_separator = (dir_len > 0 && dir_path[dir_len - 1] != '/');
    
    // Alocar memória para o caminho completo
    size_t full_path_len = dir_len + (needs_separator ? 1 : 0) + filename_len + 1;
    char *full_path = (char *)malloc(full_path_len);
    if (full_path == NULL) {
        return strdup("");
    }
    
    // Construir o caminho completo
    strcpy(full_path, dir_path);
    if (needs_separator) {
        strcat(full_path, "/");
    }
    strcat(full_path, filename);
    
    // Verificar se o arquivo existe e é um arquivo regular
    struct stat path_stat;
    if (stat(full_path, &path_stat) != 0) {
        free(full_path);
        return strdup("");
    }
    
    // Verificar se é um arquivo regular (não diretório, link simbólico, etc.)
    if (!S_ISREG(path_stat.st_mode)) {
        free(full_path);
        return strdup("");
    }
    
    // Abrir o arquivo para leitura
    FILE *file = fopen(full_path, "rb");  // Modo binário para leitura precisa
    free(full_path);  // Não precisamos mais do caminho completo
    
    if (file == NULL) {
        return strdup("");
    }
    
    // Obter o tamanho do arquivo
    if (fseek(file, 0, SEEK_END) != 0) {
        fclose(file);
        return strdup("");
    }
    
    long file_size = ftell(file);
    if (file_size < 0) {
        fclose(file);
        return strdup("");
    }
    
    // Voltar ao início do arquivo
    rewind(file);
    
    // Alocar memória para o conteúdo do arquivo + terminador nulo
    char *content = (char *)malloc(file_size + 1);
    if (content == NULL) {
        fclose(file);
        return strdup("");
    }
    
    // Ler o conteúdo do arquivo
    size_t bytes_read = fread(content, 1, file_size, file);
    fclose(file);
    
    // Verificar se leu todo o conteúdo
    if (bytes_read != (size_t)file_size) {
        free(content);
        return strdup("");
    }
    
    // Adicionar terminador nulo
    content[file_size] = '\0';
    
    return content;
}