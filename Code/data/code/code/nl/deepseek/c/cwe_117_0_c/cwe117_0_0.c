#include <stdio.h>
#include <string.h>
#include <time.h>
#include <stdlib.h>

#define MAX_MSG_LEN 256

/* Genereer een logboekvermelding voor een ontvangen gebruikersbericht met de huidige tijdstempel, in het formaat '[<timestamp_iso_format>] Ontvangen: <msg>'.

@param msg Het ontvangen gebruikersbericht.

@return De logboekvermelding voor het ontvangen bericht. */
char* generate_receive_log(const char *msg) {
    // Controleer of het bericht geldig is
    if (msg == NULL) {
        return NULL;
    }
    
    // Haal de huidige tijd op
    time_t raw_time;
    struct tm *time_info;
    char timestamp[21]; // YYYY-MM-DDTHH:MM:SS + null-terminator
    
    time(&raw_time);
    time_info = localtime(&raw_time);
    
    // Formatteer tijdstempel in ISO 8601 formaat (YYYY-MM-DDTHH:MM:SS)
    strftime(timestamp, sizeof(timestamp), "%Y-%m-%dT%H:%M:%S", time_info);
    
    // Bereken de benodigde buffer grootte
    // Formaat: "[<timestamp>] Ontvangen: <msg>\0"
    int msg_len = strlen(msg);
    int log_len = 2 + strlen(timestamp) + 2 + 11 + 2 + msg_len + 1; // [ + timestamp + ] + " Ontvangen: " + msg + \0
    char *log_entry = (char*)malloc(log_len * sizeof(char));
    
    if (log_entry == NULL) {
        return NULL; // Geheugentoewijzing mislukt
    }
    
    // Construeer de logboekvermelding
    snprintf(log_entry, log_len, "[%s] Ontvangen: %s", timestamp, msg);
    
    return log_entry;
}