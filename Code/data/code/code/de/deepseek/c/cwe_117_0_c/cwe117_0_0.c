#include <stdio.h>
#include <string.h>
#include <time.h>
#include <stdlib.h>

#define MAX_MSG_LEN 256

/* Erzeuge einen Protokolleintrag für eine empfangene Benutzer-Nachricht mit dem aktuellen Zeitstempel im Format '[<timestamp_iso_format>] Empfangen: <msg>'.

@param msg Die empfangene Benutzer-Nachricht.

@return Der Protokolleintrag für die empfangene Nachricht. */
char* generate_receive_log(const char *msg) {
    // Hole aktuelle Zeit
    time_t current_time;
    struct tm *time_info;
    char timestamp[20]; // Format: YYYY-MM-DDTHH:MM:SS + Null-Terminator
    
    time(&current_time);
    time_info = localtime(&current_time);
    
    // Erzeuge ISO 8601 Zeitstempel (vereinfachte Version: YYYY-MM-DDTHH:MM:SS)
    strftime(timestamp, sizeof(timestamp), "%Y-%m-%dT%H:%M:%S", time_info);
    
    // Berechne benötigte Länge für den Protokolleintrag
    // Format: [timestamp] Empfangen: msg
    // Länge = 1 (öffnende Klammer) + timestamp + 2 (schließende Klammer und Leerzeichen) 
    // + 10 ("Empfangen: ") + msg Länge + 1 (Null-Terminator)
    size_t msg_len = strlen(msg);
    size_t log_len = 1 + strlen(timestamp) + 2 + 10 + msg_len + 1;
    
    // Überprüfe, ob die Nachricht zu lang ist
    if (msg_len > MAX_MSG_LEN) {
        msg_len = MAX_MSG_LEN;
        log_len = 1 + strlen(timestamp) + 2 + 10 + MAX_MSG_LEN + 1;
    }
    
    // Allokiere Speicher für den Protokolleintrag
    char *log_entry = (char*)malloc(log_len);
    if (log_entry == NULL) {
        return NULL;
    }
    
    // Erzeuge den Protokolleintrag
    if (msg_len > MAX_MSG_LEN) {
        // Schneide Nachricht ab, wenn sie zu lang ist
        char truncated_msg[MAX_MSG_LEN + 1];
        strncpy(truncated_msg, msg, MAX_MSG_LEN);
        truncated_msg[MAX_MSG_LEN] = '\0';
        snprintf(log_entry, log_len, "[%s] Empfangen: %s", timestamp, truncated_msg);
    } else {
        snprintf(log_entry, log_len, "[%s] Empfangen: %s", timestamp, msg);
    }
    
    return log_entry;
}