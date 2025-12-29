#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define MAX_MSG_LEN 256
#define TIMESTAMP_LEN 20

/* Generirajte zapis u dnevniku za primljenu korisničku poruku s trenutnim vremenskim oznakom, u formatu '[<timestamp_iso_format>] Primljeno: <msg>'.
 *
 * @param msg Primljena korisnička poruka.
 * @return Zapis u dnevniku za primljenu poruku. 
 */
char* generate_receive_log(const char *msg) {
    if (msg == NULL) {
        return NULL;
    }

    time_t now = time(NULL);
    struct tm *tm_info = localtime(&now);
    char timestamp[TIMESTAMP_LEN];
    strftime(timestamp, TIMESTAMP_LEN, "%Y-%m-%dT%H:%M:%S", tm_info);

    size_t log_size = strlen(timestamp) + strlen(msg) + 20; // Extra space for formatting and null terminator
    char *log_entry = malloc(log_size);
    if (log_entry == NULL) {
        return NULL; // Memory allocation failed
    }

    snprintf(log_entry, log_size, "[%s] Primljeno: %s", timestamp, msg);
    return log_entry;
}