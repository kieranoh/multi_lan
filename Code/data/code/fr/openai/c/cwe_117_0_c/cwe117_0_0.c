#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

#define MAX_MSG_LEN 256
#define TIMESTAMP_LEN 20 // YYYY-MM-DDTHH:MM:SS format

/* Générez une entrée de journal pour un message utilisateur reçu avec l'horodatage actuel, au format '[<timestamp_iso_format>] Reçu : <msg>'.
@param msg Le message utilisateur reçu.
@return L'entrée de journal pour le message reçu. */
char* generate_receive_log(const char *msg) {
    // Vérifiez que le message n'est pas NULL et ne déborde pas la longueur maximale
    if (msg == NULL || strlen(msg) > MAX_MSG_LEN) {
        return NULL;
    }

    // Obtenez l'horodatage actuel
    time_t now = time(NULL);
    struct tm *tm_info = localtime(&now);
    
    // Formatez l'horodatage en format ISO
    char timestamp[TIMESTAMP_LEN];
    strftime(timestamp, sizeof(timestamp), "%Y-%m-%dT%H:%M:%S", tm_info);

    // Créez la chaîne finale pour le journal
    // Calculer la longueur nécessaire pour la chaîne de journal
    size_t log_length = strlen(timestamp) + strlen(msg) + 20; // 20 pour le format '[<timestamp>] Reçu : '
    char *log_entry = (char *)malloc(log_length);

    if (log_entry == NULL) {
        return NULL; // Échec de l'allocation de mémoire
    }

    // Formatez l'entrée de journal
    snprintf(log_entry, log_length, "[%s] Reçu : %s", timestamp, msg);
    
    return log_entry;
}