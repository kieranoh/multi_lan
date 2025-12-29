#include <stdio.h>
#include <time.h>
#include <string.h>
#include <stdlib.h>

#define MAX_MSG_LEN 256
#define TIMESTAMP_LEN 20

/* Generálj egy naplóbejegyzést egy beérkezett felhasználói üzenetről a jelenlegi időbélyeggel, a következő formátumban: '[<timestamp_iso_format>] Received: <msg>'.
@param msg A beérkezett felhasználói üzenet.
@return A naplóbejegyzés a beérkezett üzenetről. */
char* generate_receive_log(const char *msg) {
    time_t now;
    struct tm *tm_info;
    char timestamp[TIMESTAMP_LEN];
    char *log_entry;

    // Ellenőrizzük, hogy a msg érvényes-e
    if (msg == NULL || strlen(msg) >= MAX_MSG_LEN) {
        return NULL;
    }

    // Jelenlegi idő lekérése
    time(&now);
    tm_info = localtime(&now);

    // ISO formátumú időbélyeg generálása
    strftime(timestamp, TIMESTAMP_LEN, "%Y-%m-%dT%H:%M:%S", tm_info);

    // Memória allokálása a naplóbejegyzésnek
    log_entry = malloc(strlen(timestamp) + strlen(msg) + 20); // 20 az extra karaktereknek

    if (log_entry == NULL) {
        return NULL; // Hiba a memória allokálásakor
    }

    // Naplóbejegyzés létrehozása
    snprintf(log_entry, strlen(timestamp) + strlen(msg) + 20, "[%s] Received: %s", timestamp, msg);

    return log_entry;
}