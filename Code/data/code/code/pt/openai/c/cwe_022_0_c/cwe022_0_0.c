#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char *read_file_from_dir(const char *filename, const char *dir_path) {
    // Monta o caminho completo do arquivo
    size_t path_len = strlen(dir_path) + strlen(filename) + 2; // +2 para '/' e '\0'
    char *full_path = (char *)malloc(path_len);
    if (full_path == NULL) {
        return ""; // Retorna string vazia em caso de erro de alocação
    }
    
    snprintf(full_path, path_len, "%s/%s", dir_path, filename);
    
    // Abre o arquivo para leitura
    FILE *file = fopen(full_path, "r");
    free(full_path); // Libera o caminho completo após abrir o arquivo
    if (file == NULL) {
        return ""; // Retorna string vazia se o arquivo não puder ser aberto
    }

    // Move o ponteiro do arquivo para o final para obter o tamanho do arquivo
    fseek(file, 0, SEEK_END);
    long length = ftell(file);
    fseek(file, 0, SEEK_SET); // Retorna ao início do arquivo

    // Aloca memória para o conteúdo do arquivo
    char *content = (char *)malloc(length + 1); // +1 para o caractere nulo
    if (content == NULL) {
        fclose(file);
        return ""; // Retorna string vazia se a alocação falhar
    }

    // Lê o conteúdo do arquivo
    fread(content, 1, length, file);
    content[length] = '\0'; // Adiciona o caractere nulo ao final

    fclose(file); // Fecha o arquivo
    return content; // Retorna o conteúdo lido
}