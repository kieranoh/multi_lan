#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define MAX_MSG_LEN 256
#define TIMESTAMP_LEN 20 // Format: YYYY-MM-DDTHH:MM:SS

/* Generišite zapis u dnevniku za primljenu korisničku poruku sa trenutnim vremenskim pečatom, u formatu '[<timestamp_iso_format>] Primljeno: <msg>'.
 
@param msg Primljena korisnička poruka.

@return Zapis u dnevniku za primljenu poruku. */
char* generate_receive_log(const char *msg) {
    if (msg == NULL) {
        return NULL;
    }

    char *log_entry = (char *)malloc(MAX_MSG_LEN + TIMESTAMP_LEN + 30); // Allocating enough space
    if (log_entry == NULL) {
        return NULL; // Allocation failed
    }

    time_t rawtime;
    struct tm *timeinfo;
    char timestamp[TIMESTAMP_LEN];

    time(&rawtime);
    timeinfo = localtime(&rawtime);
    strftime(timestamp, TIMESTAMP_LEN, "%Y-%m-%dT%H:%M:%S", timeinfo);

    snprintf(log_entry, MAX_MSG_LEN + TIMESTAMP_LEN + 30, "[%s] Primljeno: %s", timestamp, msg);
    
    return log_entry;
}