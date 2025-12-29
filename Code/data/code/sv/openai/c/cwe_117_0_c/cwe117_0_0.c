#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define MAX_MSG_LEN 256
#define TIMESTAMP_LEN 20 // YYYY-MM-DDTHH:MM:SS format

/* Generera en loggpost för ett mottaget användarmeddelande med den aktuella tidsstämpeln, i formatet '[<timestamp_iso_format>] Mottaget: <msg>'.
@param msg Det mottagna användarmeddelandet.
@return Loggposten för det mottagna meddelandet. */
char* generate_receive_log(const char *msg) {
    // Kontrollera att meddelandet inte är NULL och inom längdgränserna
    if (msg == NULL || strlen(msg) > MAX_MSG_LEN) {
        return NULL;
    }

    // Allokera minne för loggposten
    char *log_entry = (char *)malloc(MAX_MSG_LEN + TIMESTAMP_LEN + 50); // Extra utrymme för formatet
    if (log_entry == NULL) {
        return NULL; // Kontrollera att allokering lyckades
    }

    // Hämta den aktuella tiden
    time_t now = time(NULL);
    struct tm *t = localtime(&now);
    char timestamp[TIMESTAMP_LEN];

    // Formatera tidsstämpeln
    strftime(timestamp, sizeof(timestamp), "%Y-%m-%dT%H:%M:%S", t);

    // Generera loggposten
    snprintf(log_entry, MAX_MSG_LEN + TIMESTAMP_LEN + 50, "[%s] Mottaget: %s", timestamp, msg);

    return log_entry;
}