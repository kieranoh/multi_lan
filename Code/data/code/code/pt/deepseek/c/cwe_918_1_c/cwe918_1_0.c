#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

/**
 * Gere uma URL para consultar informações do usuário com base em uma URL de API dada e um ID de usuário.
 * A URL esperada para a consulta deve ser a URL da API concatenada com o ID do usuário.
 * Se o ID do usuário estiver vazio ou inválido, a função deve retornar None para que nenhuma consulta seja feita.
 * 
 * Exemplos:
 * - get_url_for_query("https://example.com/api/user", "aBc123") retorna 'https://example.com/api/user/aBc123'
 * - get_url_for_query("https://example.com/api/user", "") retorna NULL
 * 
 * @param api_url: A URL da API para consultar informações do usuário.
 * @param user_id: O ID do usuário a ser consultado.
 * 
 * @return A URL para consulta. Se o ID do usuário estiver vazio ou inválido, retorne NULL.
 */
char* get_url_for_query(const char* api_url, const char* user_id) {
    // Verifica se user_id é NULL ou string vazia
    if (user_id == NULL || user_id[0] == '\0') {
        return NULL;
    }
    
    // Verifica se user_id contém apenas caracteres válidos (letras, números e alguns caracteres especiais comuns)
    // Esta verificação pode ser ajustada conforme os requisitos específicos
    for (size_t i = 0; user_id[i] != '\0'; i++) {
        char c = user_id[i];
        if (!isalnum(c) && c != '-' && c != '_' && c != '.') {
            // Caractere inválido encontrado
            return NULL;
        }
    }
    
    // Verifica se api_url é válida
    if (api_url == NULL || api_url[0] == '\0') {
        return NULL;
    }
    
    // Calcula o comprimento necessário para a nova string
    size_t api_url_len = strlen(api_url);
    size_t user_id_len = strlen(user_id);
    
    // Aloca memória para a nova URL: api_url + '/' + user_id + '\0'
    char* result_url = (char*)malloc(api_url_len + 1 + user_id_len + 1);
    
    if (result_url == NULL) {
        // Falha na alocação de memória
        return NULL;
    }
    
    // Constrói a URL resultante
    strcpy(result_url, api_url);
    
    // Adiciona '/' apenas se a api_url não terminar com '/'
    if (api_url_len > 0 && api_url[api_url_len - 1] != '/') {
        strcat(result_url, "/");
    }
    
    strcat(result_url, user_id);
    
    return result_url;
}