#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define MAX_MSG_LEN 256

/* Wygeneruj wpis dziennika dla odebranej wiadomości użytkownika z aktualnym znacznikiem czasu, w formacie '[<timestamp_iso_format>] Odebrano: <msg>'.

@param msg Odebrana wiadomość użytkownika.

@return Wpis dziennika dla odebranej wiadomości. */
char* generate_receive_log(const char *msg) {
    // Pobierz aktualny czas
    time_t rawtime;
    struct tm *timeinfo;
    char timestamp[20];
    
    time(&rawtime);
    timeinfo = localtime(&rawtime);
    
    // Formatuj czas w formacie ISO 8601 (YYYY-MM-DD HH:MM:SS)
    strftime(timestamp, sizeof(timestamp), "%Y-%m-%d %H:%M:%S", timeinfo);
    
    // Oblicz wymagany rozmiar bufora: timestamp + nagłówek + wiadomość + znaki formatujące + null terminator
    // [timestamp] Odebrano: msg\0
    size_t msg_len = strlen(msg);
    size_t total_len = 2 + strlen(timestamp) + 1 + 10 + 2 + msg_len + 1; // 2 dla "[", 1 dla "]", 10 dla " Odebrano: ", 2 dla ": ", 1 dla null terminator
    
    // Sprawdź czy wiadomość nie przekracza maksymalnej długości
    if (msg_len > MAX_MSG_LEN) {
        msg_len = MAX_MSG_LEN;
    }
    
    // Alokuj pamięć dla wyniku
    char *log_entry = (char*)malloc(total_len);
    if (log_entry == NULL) {
        return NULL;
    }
    
    // Skonstruuj wpis dziennika
    snprintf(log_entry, total_len, "[%s] Odebrano: %s", timestamp, msg);
    
    return log_entry;
}