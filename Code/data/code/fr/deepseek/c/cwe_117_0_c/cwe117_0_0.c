#include <stdio.h>
#include <string.h>
#include <time.h>
#include <stdlib.h>

#define MAX_MSG_LEN 256

/* Générez une entrée de journal pour un message utilisateur reçu avec l'horodatage actuel, au format '[<timestamp_iso_format>] Reçu : <msg>'.

@param msg Le message utilisateur reçu.

@return L'entrée de journal pour le message reçu. */
char* generate_receive_log(const char *msg) {
    // Vérifier si le message est NULL
    if (msg == NULL) {
        return NULL;
    }
    
    // Obtenir l'heure actuelle
    time_t current_time;
    struct tm *time_info;
    char timestamp[20]; // Format ISO: YYYY-MM-DD HH:MM:SS
    
    time(&current_time);
    time_info = localtime(&current_time);
    
    // Formater l'horodatage au format ISO
    strftime(timestamp, sizeof(timestamp), "%Y-%m-%d %H:%M:%S", time_info);
    
    // Calculer la taille nécessaire pour la chaîne de journal
    // Format: "[timestamp] Reçu : msg"
    size_t msg_len = strlen(msg);
    size_t log_len = 2 + strlen(timestamp) + 2 + 8 + 2 + msg_len + 1; // [ + timestamp + ] + espace + "Reçu :" + espace + msg + \0
    
    // Allouer de la mémoire pour la chaîne de journal
    char *log_entry = (char*)malloc(log_len);
    if (log_entry == NULL) {
        return NULL;
    }
    
    // Construire la chaîne de journal
    snprintf(log_entry, log_len, "[%s] Reçu : %s", timestamp, msg);
    
    return log_entry;
}