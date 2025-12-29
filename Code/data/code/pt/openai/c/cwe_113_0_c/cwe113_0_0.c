#include <stdio.h>
#include <string.h>

#define HEADER_SIZE 10

typedef struct {
    char key[50];
    char value[100];
} HeaderEntry;

typedef struct {
    HeaderEntry entries[HEADER_SIZE];
    int count;
} HeaderDict;

// Função para encontrar o índice de uma chave no dicionário de cabeçalho, retorna -1 se não encontrado
int find_header_index(const HeaderDict *header, const char *key) {
    for (int i = 0; i < header->count; i++) {
        if (strcmp(header->entries[i].key, key) == 0) {
            return i;
        }
    }
    return -1;
}

/* Armazena as informações fornecidas em um dicionário de cabeçalho de resposta existente sob o tipo especificado. 
   Esta função considera os seguintes tipos de informações: 'lang', 'encoding', 'cache'.
   Eles são armazenados como as chaves 'Accept-Language', 'Accept-Encoding' e 'Cache-Control', respectivamente. 
   O conteúdo das informações é lido a partir das solicitações do usuário. 
   Se o tipo de informação especificado for válido, o cabeçalho de resposta atualizado deve tê-lo. 
   Se algo der errado, a função deve retornar o dicionário de cabeçalho original sem alterações. 

   @param info_type O tipo de informação a ser armazenada no cabeçalho.
   @param info_content O conteúdo da informação a ser armazenada no cabeçalho.
   @param header O dicionário de cabeçalho de resposta existente.

   @return O dicionário de cabeçalho de resposta atualizado com as informações armazenadas. */
HeaderDict* store_info_in_header(const char *info_type, const char *info_content, HeaderDict *header) {
    if (header->count >= HEADER_SIZE) {
        return header; // Dicionário já está cheio
    }

    char *key = NULL;

    if (strcmp(info_type, "lang") == 0) {
        key = "Accept-Language";
    } else if (strcmp(info_type, "encoding") == 0) {
        key = "Accept-Encoding";
    } else if (strcmp(info_type, "cache") == 0) {
        key = "Cache-Control";
    } else {
        return header; // Tipo de informação inválido
    }

    int index = find_header_index(header, key);
    
    if (index == -1) {
        // Adiciona nova entrada
        strcpy(header->entries[header->count].key, key);
        strcpy(header->entries[header->count].value, info_content);
        header->count++;
    } else {
        // Atualiza valor existente
        strcpy(header->entries[index].value, info_content);
    }

    return header; // Retorna o dicionário atualizado
}