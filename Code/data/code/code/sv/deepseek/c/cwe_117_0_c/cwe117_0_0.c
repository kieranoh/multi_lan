#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define MAX_MSG_LEN 256

/* Generera en loggpost för ett mottaget användarmeddelande med den aktuella tidsstämpeln, i formatet '[<timestamp_iso_format>] Mottaget: <msg>'.

@param msg Det mottagna användarmeddelandet.

@return Loggposten för det mottagna meddelandet. */
char* generate_receive_log(const char *msg) {
    // Hämta aktuell tid
    time_t rawtime;
    struct tm *timeinfo;
    char timestamp[20];
    
    time(&rawtime);
    timeinfo = localtime(&rawtime);
    
    // Formatera tiden som ISO-format (YYYY-MM-DD HH:MM:SS)
    strftime(timestamp, sizeof(timestamp), "%Y-%m-%d %H:%M:%S", timeinfo);
    
    // Beräkna längden på den slutliga strängen
    // Format: "[<timestamp>] Mottaget: <msg>\0"
    int timestamp_len = strlen(timestamp);
    int msg_len = strlen(msg);
    int prefix_len = strlen("[] Mottaget: ");
    
    int total_len = timestamp_len + prefix_len + msg_len + 1; // +1 för null-terminator
    
    // Allokera minne för loggposten
    char *log_entry = (char*)malloc(total_len * sizeof(char));
    if (log_entry == NULL) {
        return NULL; // Minnesallokering misslyckades
    }
    
    // Bygg loggposten
    snprintf(log_entry, total_len, "[%s] Mottaget: %s", timestamp, msg);
    
    return log_entry;
}