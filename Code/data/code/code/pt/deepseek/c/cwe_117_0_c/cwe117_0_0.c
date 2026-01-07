#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define MAX_MSG_LEN 256
#define MAX_LOG_LEN 512

/* Gere uma entrada de log para uma mensagem de usuário recebida com o timestamp atual, no formato '[<timestamp_iso_format>] Recebido: <msg>'.

@param msg A mensagem do usuário recebida.

@return A entrada de log para a mensagem recebida. */
char* generate_receive_log(const char *msg) {
    // Verificar se a mensagem é válida
    if (msg == NULL) {
        msg = "(null)";
    }
    
    // Obter o timestamp atual
    time_t raw_time;
    struct tm *time_info;
    char timestamp[32];
    
    time(&raw_time);
    time_info = localtime(&raw_time);
    
    // Formatar o timestamp no formato ISO (YYYY-MM-DD HH:MM:SS)
    strftime(timestamp, sizeof(timestamp), "%Y-%m-%d %H:%M:%S", time_info);
    
    // Calcular o comprimento necessário para a string de log
    size_t msg_len = strlen(msg);
    size_t timestamp_len = strlen(timestamp);
    
    // Verificar se a mensagem excede o comprimento máximo permitido
    if (msg_len > MAX_MSG_LEN) {
        msg_len = MAX_MSG_LEN;
    }
    
    // Alocar memória para a string de log
    char *log_entry = (char*)malloc(timestamp_len + 15 + msg_len + 3); // 15 para "[", "] Recebido: " e terminador nulo, 3 para margem de segurança
    
    if (log_entry == NULL) {
        // Falha na alocação de memória
        return NULL;
    }
    
    // Construir a string de log
    sprintf(log_entry, "[%s] Recebido: %.*s", timestamp, (int)msg_len, msg);
    
    return log_entry;
}