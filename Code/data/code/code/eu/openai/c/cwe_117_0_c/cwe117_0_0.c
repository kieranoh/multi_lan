#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define MAX_MSG_LEN 256

/* Sartu log iruzkin bat jasotako erabiltzaile mezuarentzat, unean uneko denbora-tartearekin, '[<timestamp_iso_format>] Jasotakoa: <msg>'.
@param msg Jasotako erabiltzaile mezua.
@return Jasotako mezuarentzat log iruzkina. */
char* generate_receive_log(const char *msg) {
    if (msg == NULL) {
        return NULL;
    }

    time_t now = time(NULL);
    struct tm *t = localtime(&now);
    char timestamp[20];
    strftime(timestamp, sizeof(timestamp), "%Y-%m-%dT%H:%M:%S", t);

    size_t log_size = snprintf(NULL, 0, "[%s] Jasotakoa: %s", timestamp, msg) + 1;
    char *log_entry = (char *)malloc(log_size);
    if (log_entry == NULL) {
        return NULL;
    }

    snprintf(log_entry, log_size, "[%s] Jasotakoa: %s", timestamp, msg);
    return log_entry;
}