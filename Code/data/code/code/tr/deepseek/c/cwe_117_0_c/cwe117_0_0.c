#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define MAX_MSG_LEN 256

/* Gelen bir kullanıcı mesajı için mevcut zaman damgasıyla bir günlük girişi oluşturun, formatı '[<timestamp_iso_format>] Alındı: <msg>'.

@param msg Alınan kullanıcı mesajı.

@return Alınan mesaj için günlük girişi. */
char* generate_receive_log(const char *msg) {
    // NULL kontrolü
    if (msg == NULL) {
        msg = "(null mesaj)";
    }
    
    // ISO 8601 formatında zaman damgası al
    time_t rawtime;
    struct tm *timeinfo;
    char timestamp[21]; // YYYY-MM-DDTHH:MM:SS\0 (20 karakter + null terminator)
    
    time(&rawtime);
    timeinfo = localtime(&rawtime);
    
    // ISO 8601 formatında zaman damgası oluştur
    strftime(timestamp, sizeof(timestamp), "%Y-%m-%dT%H:%M:%S", timeinfo);
    
    // Günlük girişi için gerekli bellek miktarını hesapla
    // Format: [timestamp] Alındı: msg
    int msg_len = strlen(msg);
    int log_len = 2 + strlen(timestamp) + 2 + 9 + 2 + msg_len + 1; // [] + timestamp + boşluk + "Alındı:" + ": " + msg + null terminator
    
    // Bellek tahsisi
    char *log_entry = (char*)malloc(log_len * sizeof(char));
    if (log_entry == NULL) {
        return NULL;
    }
    
    // Günlük girişini formatla
    snprintf(log_entry, log_len, "[%s] Alındı: %s", timestamp, msg);
    
    return log_entry;
}