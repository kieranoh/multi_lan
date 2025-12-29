#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

char* write_results(const char* results) {
    // Verificar se a entrada é válida
    if (results == NULL) {
        return NULL;
    }
    
    // Criar um template para o arquivo temporário
    char template[] = "/tmp/results_XXXXXX";
    int fd = mkstemp(template);
    
    if (fd == -1) {
        // Falha ao criar arquivo temporário
        return NULL;
    }
    
    // Escrever os resultados no arquivo
    size_t len = strlen(results);
    ssize_t written = write(fd, results, len);
    
    if (written != (ssize_t)len) {
        // Falha ao escrever no arquivo
        close(fd);
        unlink(template); // Remover o arquivo
        return NULL;
    }
    
    // Fechar o arquivo
    close(fd);
    
    // Alocar memória para o nome do arquivo
    char* filename = malloc(strlen(template) + 1);
    if (filename == NULL) {
        unlink(template); // Remover o arquivo se falhar na alocação
        return NULL;
    }
    
    // Copiar o nome do arquivo para a memória alocada
    strcpy(filename, template);
    
    return filename;
}