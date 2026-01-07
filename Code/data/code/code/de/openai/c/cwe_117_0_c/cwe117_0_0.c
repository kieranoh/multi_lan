#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define MAX_MSG_LEN 256

/* Erzeuge einen Protokolleintrag für eine empfangene Benutzer-Nachricht mit dem aktuellen Zeitstempel im Format '[<timestamp_iso_format>] Empfangen: <msg>'.
  
@param msg Die empfangene Benutzer-Nachricht.

@return Der Protokolleintrag für die empfangene Nachricht. */
char* generate_receive_log(const char *msg) {
    if (msg == NULL) {
        return NULL;
    }

    time_t rawtime;
    struct tm *timeinfo;
    char timestamp[20]; // Puffer für das ISO-Format: YYYY-MM-DDTHH:MM:SS
    char *log_entry;

    // Aktuellen Zeitstempel abrufen
    time(&rawtime);
    timeinfo = localtime(&rawtime);
    strftime(timestamp, sizeof(timestamp), "%Y-%m-%dT%H:%M:%S", timeinfo);

    // Protokolleintrag formatieren
    size_t msg_len = strlen(msg);
    size_t log_len = strlen(timestamp) + msg_len + 27; // Länge des Formats: [<timestamp>] Empfangen: <msg>

    log_entry = (char *)malloc(log_len);
    if (log_entry == NULL) {
        return NULL; // Speicherzuweisung fehlgeschlagen
    }

    snprintf(log_entry, log_len, "[%s] Empfangen: %s", timestamp, msg);
    return log_entry;
}