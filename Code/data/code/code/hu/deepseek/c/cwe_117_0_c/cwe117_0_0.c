#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define MAX_MSG_LEN 256

/* Generálj egy naplóbejegyzést egy beérkezett felhasználói üzenetről a jelenlegi időbélyeggel, a következő formátumban: '[<timestamp_iso_format>] Received: <msg>'.

@param msg A beérkezett felhasználói üzenet.

@return A naplóbejegyzés a beérkezett üzenetről. */
char* generate_receive_log(const char *msg) {
    // Ellenőrizzük, hogy az üzenet nem NULL
    if (msg == NULL) {
        msg = "(null message)";
    }
    
    // Jelenlegi idő lekérése
    time_t now = time(NULL);
    struct tm *tm_info = localtime(&now);
    
    // ISO formátumú időbélyeg: YYYY-MM-DD HH:MM:SS
    char timestamp[20];
    strftime(timestamp, sizeof(timestamp), "%Y-%m-%d %H:%M:%S", tm_info);
    
    // Számítsuk ki a szükséges buffer méretet
    // Formátum: "[<timestamp>] Received: <msg>\0"
    // timestamp: 19 karakter + 1 null
    // fix szöveg: "] Received: " = 12 karakter
    // üzenet: strlen(msg) karakter
    // záró null: 1 karakter
    size_t total_len = 1 + 19 + 12 + strlen(msg) + 1; // [ + timestamp + ] Received: + msg + \0
    
    // Memória foglalása a naplóbejegyzéshez
    char *log_entry = (char*)malloc(total_len);
    if (log_entry == NULL) {
        return NULL;
    }
    
    // Naplóbejegyzés összeállítása
    snprintf(log_entry, total_len, "[%s] Received: %s", timestamp, msg);
    
    return log_entry;
}