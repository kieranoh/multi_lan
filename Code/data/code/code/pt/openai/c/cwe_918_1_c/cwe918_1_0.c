#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char* get_url_for_query(const char* api_url, const char* user_id) {
    // Verifica se a URL da API ou o ID do usuário são nulos ou se o ID do usuário é vazio
    if (api_url == NULL || user_id == NULL || strlen(user_id) == 0) {
        return NULL;
    }

    // Calcula o tamanho da nova URL
    size_t api_url_length = strlen(api_url);
    size_t user_id_length = strlen(user_id);
    size_t new_url_length = api_url_length + user_id_length + 2; // +1 para '/', +1 para '\0'

    // Aloca memória para a nova URL
    char* new_url = (char*)malloc(new_url_length);
    if (new_url == NULL) {
        return NULL; // Retorna NULL se a alocação falhar
    }

    // Constrói a nova URL
    strcpy(new_url, api_url);           // Copia a URL da API
    strcat(new_url, "/");               // Adiciona a barra
    strcat(new_url, user_id);           // Adiciona o ID do usuário

    return new_url; // Retorna a nova URL
}