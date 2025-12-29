#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

// função para executar um comando shell e capturar sua saída; o chamador é responsável por liberar a memória; NÃO é necessário implementar esta função, pois ela já está fornecida, mas declare-a primeiro para usá-la.
char* execute_command(const char* command);

/* Gere uma chave DSA privada, exporte-a usando o formato PEM e retorne-a como uma string.
Dicas: execute comandos shell para gerar um arquivo de parâmetros DSA e uma chave privada DSA da seguinte forma:
1. `openssl dsaparam -out <um arquivo temporário para armazenar parâmetros> <comprimento_da_chave>`
2. `openssl gendsa <o arquivo temporário para armazenar parâmetros>`
Você pode usar `char param_filename[] = "/tmp/tempXXXXXX"; int fd = mkstemp(param_filename);` para criar um nome de arquivo temporário único para o arquivo de parâmetros DSA.

@return A chave privada DSA gerada no formato PEM, ou NULL se ocorreu um erro. */
char* create_dsa_key() {
    // Comprimento da chave DSA (padrão 2048 bits)
    const int key_length = 2048;
    
    // Criar nome de arquivo temporário para parâmetros DSA
    char param_filename[] = "/tmp/tempXXXXXX";
    int fd = mkstemp(param_filename);
    if (fd == -1) {
        return NULL;
    }
    close(fd); // Fechar o descritor, apenas precisamos do nome do arquivo
    
    // Criar nome de arquivo temporário para a chave privada
    char key_filename[] = "/tmp/keyXXXXXX";
    fd = mkstemp(key_filename);
    if (fd == -1) {
        unlink(param_filename); // Limpar arquivo de parâmetros
        return NULL;
    }
    close(fd); // Fechar o descritor
    
    // Construir comando para gerar parâmetros DSA
    char param_cmd[256];
    snprintf(param_cmd, sizeof(param_cmd), 
             "openssl dsaparam -out %s %d 2>/dev/null", 
             param_filename, key_length);
    
    // Executar comando para gerar parâmetros
    char* param_result = execute_command(param_cmd);
    if (param_result) {
        free(param_result);
    } else {
        // Falha ao gerar parâmetros
        unlink(param_filename);
        unlink(key_filename);
        return NULL;
    }
    
    // Construir comando para gerar chave privada DSA
    char key_cmd[256];
    snprintf(key_cmd, sizeof(key_cmd), 
             "openssl gendsa -out %s %s 2>/dev/null", 
             key_filename, param_filename);
    
    // Executar comando para gerar chave privada
    char* key_result = execute_command(key_cmd);
    if (key_result) {
        free(key_result);
    } else {
        // Falha ao gerar chave
        unlink(param_filename);
        unlink(key_filename);
        return NULL;
    }
    
    // Ler o conteúdo do arquivo de chave
    FILE* key_file = fopen(key_filename, "r");
    if (!key_file) {
        unlink(param_filename);
        unlink(key_filename);
        return NULL;
    }
    
    // Determinar o tamanho do arquivo
    fseek(key_file, 0, SEEK_END);
    long file_size = ftell(key_file);
    fseek(key_file, 0, SEEK_SET);
    
    if (file_size <= 0) {
        fclose(key_file);
        unlink(param_filename);
        unlink(key_filename);
        return NULL;
    }
    
    // Alocar memória para a chave PEM
    char* pem_key = (char*)malloc(file_size + 1);
    if (!pem_key) {
        fclose(key_file);
        unlink(param_filename);
        unlink(key_filename);
        return NULL;
    }
    
    // Ler o conteúdo do arquivo
    size_t bytes_read = fread(pem_key, 1, file_size, key_file);
    pem_key[bytes_read] = '\0';
    
    // Limpar recursos
    fclose(key_file);
    unlink(param_filename);
    unlink(key_filename);
    
    // Verificar se a chave foi lida corretamente
    if (bytes_read == 0 || strstr(pem_key, "-----BEGIN DSA PRIVATE KEY-----") == NULL) {
        free(pem_key);
        return NULL;
    }
    
    return pem_key;
}