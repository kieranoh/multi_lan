#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

char* write_results(const char* results) {
    // Criar um nome de arquivo temporário
    char* filename = malloc(L_tmpnam);
    if (filename == NULL) {
        return NULL; // Falha na alocação de memória
    }
    
    // Gerar um nome de arquivo temporário
    tmpnam(filename);
    
    // Criar e abrir o arquivo para escrita
    FILE* file = fopen(filename, "w");
    if (file == NULL) {
        free(filename);
        return NULL; // Falha ao abrir arquivo
    }
    
    // Escrever os resultados no arquivo
    fprintf(file, "%s", results);
    
    // Fechar o arquivo
    fclose(file);
    
    // Retornar o nome do arquivo temporário
    return filename;
}