#include <string.h>
#include <stdio.h>

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

/* Armazena as informações fornecidas em um dicionário de cabeçalho de resposta existente sob o tipo especificado. Esta função considera os seguintes tipos de informações: 'lang', 'encoding', 'cache'. Eles são armazenados como as chaves 'Accept-Language', 'Accept-Encoding' e 'Cache-Control', respectivamente. O conteúdo das informações é lido a partir das solicitações do usuário. Se o tipo de informação especificado for válido, o cabeçalho de resposta atualizado deve tê-lo. Se algo der errado, a função deve retornar o dicionário de cabeçalho original sem alterações.

@param info_type O tipo de informação a ser armazenada no cabeçalho.
@param info_content O conteúdo da informação a ser armazenada no cabeçalho.
@param header O dicionário de cabeçalho de resposta existente.

@return O dicionário de cabeçalho de resposta atualizado com as informações armazenadas. */
HeaderDict* store_info_in_header(const char *info_type, const char *info_content, HeaderDict *header) {
    // Verificar se os parâmetros de entrada são válidos
    if (info_type == NULL || info_content == NULL || header == NULL) {
        return header;
    }
    
    // Verificar se o dicionário de cabeçalho é válido
    if (header->count < 0 || header->count > HEADER_SIZE) {
        return header;
    }
    
    // Determinar a chave do cabeçalho com base no tipo de informação
    const char *header_key = NULL;
    
    if (strcmp(info_type, "lang") == 0) {
        header_key = "Accept-Language";
    } else if (strcmp(info_type, "encoding") == 0) {
        header_key = "Accept-Encoding";
    } else if (strcmp(info_type, "cache") == 0) {
        header_key = "Cache-Control";
    } else {
        // Tipo de informação inválido, retornar o cabeçalho original
        return header;
    }
    
    // Verificar se a chave já existe no dicionário
    int existing_index = find_header_index(header, header_key);
    
    if (existing_index != -1) {
        // Atualizar o valor existente
        strncpy(header->entries[existing_index].value, info_content, sizeof(header->entries[existing_index].value) - 1);
        header->entries[existing_index].value[sizeof(header->entries[existing_index].value) - 1] = '\0';
    } else {
        // Adicionar nova entrada se houver espaço
        if (header->count >= HEADER_SIZE) {
            // Não há espaço disponível, retornar o cabeçalho original
            return header;
        }
        
        // Copiar a chave e o valor para a nova entrada
        strncpy(header->entries[header->count].key, header_key, sizeof(header->entries[header->count].key) - 1);
        header->entries[header->count].key[sizeof(header->entries[header->count].key) - 1] = '\0';
        
        strncpy(header->entries[header->count].value, info_content, sizeof(header->entries[header->count].value) - 1);
        header->entries[header->count].value[sizeof(header->entries[header->count].value) - 1] = '\0';
        
        // Incrementar o contador
        header->count++;
    }
    
    return header;
}