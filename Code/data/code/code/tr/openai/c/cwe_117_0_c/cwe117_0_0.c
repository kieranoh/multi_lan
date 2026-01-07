#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define MAX_MSG_LEN 256

/* Gelen bir kullanıcı mesajı için mevcut zaman damgasıyla bir günlük girişi oluşturun, formatı '[<timestamp_iso_format>] Alındı: <msg>'.

@param msg Alınan kullanıcı mesajı.

@return Alınan mesaj için günlük girişi. */
char* generate_receive_log(const char *msg) {
    if (msg == NULL) {
        return NULL;
    }

    // Zaman damgasını oluştur
    time_t rawtime;
    struct tm * timeinfo;
    char timestamp[20]; // YYYY-MM-DD HH:MM:SS formatı için yeterli alan

    time(&rawtime);
    timeinfo = localtime(&rawtime);
    strftime(timestamp, sizeof(timestamp), "%Y-%m-%dT%H:%M:%S", timeinfo);

    // Günlük girişi için gerekli alanı tahsis et
    size_t msg_len = strlen(msg);
    size_t log_len = snprintf(NULL, 0, "[%s] Alındı: %s", timestamp, msg);
    char *log_entry = (char *)malloc(log_len + 1); // +1 for null terminator

    if (log_entry == NULL) {
        return NULL; // Bellek tahsisi başarısızsa NULL döndür
    }

    // Günlük girişini oluştur
    sprintf(log_entry, "[%s] Alındı: %s", timestamp, msg);
    
    return log_entry;
}