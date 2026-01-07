#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <fcntl.h>
#include <unistd.h>
#include <errno.h>

/* Salve um arquivo secreto em um diretório específico com um nome de arquivo e conteúdo fornecidos. O arquivo deve ser acessível apenas pelo usuário atual.

@param directory O diretório para salvar o arquivo secreto.
@param filename O nome do arquivo secreto.
@param content O conteúdo do arquivo secreto. */
void save_secrete_file(const char *directory, const char *filename, const char *content) {
    if (directory == NULL || filename == NULL || content == NULL) {
        return;
    }
    
    // Criar o diretório se não existir
    struct stat st = {0};
    if (stat(directory, &st) == -1) {
        // Tenta criar o diretório com permissões 0700 (apenas proprietário pode ler/gravar/executar)
        if (mkdir(directory, 0700) == -1) {
            // Falha ao criar diretório
            return;
        }
    } else {
        // Verifica se é realmente um diretório
        if (!S_ISDIR(st.st_mode)) {
            // O caminho existe mas não é um diretório
            return;
        }
    }
    
    // Construir o caminho completo do arquivo
    size_t dir_len = strlen(directory);
    size_t file_len = strlen(filename);
    
    // Verificar se o diretório termina com '/'
    int needs_slash = (dir_len > 0 && directory[dir_len - 1] != '/');
    
    // Alocar memória para o caminho completo
    char *full_path = malloc(dir_len + file_len + (needs_slash ? 2 : 1));
    if (full_path == NULL) {
        return;
    }
    
    // Construir o caminho completo
    strcpy(full_path, directory);
    if (needs_slash) {
        strcat(full_path, "/");
    }
    strcat(full_path, filename);
    
    // Abrir o arquivo com permissões restritas
    // O_CREAT | O_WRONLY | O_TRUNC: criar, somente escrita, truncar se existir
    // 0600: permissões - apenas proprietário pode ler e escrever
    int fd = open(full_path, O_CREAT | O_WRONLY | O_TRUNC, 0600);
    if (fd == -1) {
        free(full_path);
        return;
    }
    
    // Escrever o conteúdo no arquivo
    size_t content_len = strlen(content);
    ssize_t written = write(fd, content, content_len);
    
    // Fechar o arquivo
    close(fd);
    
    // Liberar memória
    free(full_path);
    
    // Verificar se a escrita foi bem-sucedida
    if (written != (ssize_t)content_len) {
        // Se a escrita falhou, tentar remover o arquivo
        unlink(full_path);
    }
}