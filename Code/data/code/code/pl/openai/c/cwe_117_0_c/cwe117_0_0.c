#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define MAX_MSG_LEN 256
#define TIMESTAMP_LEN 20

/* Wygeneruj wpis dziennika dla odebranej wiadomości użytkownika z aktualnym znacznikiem czasu, w formacie '[<timestamp_iso_format>] Odebrano: <msg>'.

@param msg Odebrana wiadomość użytkownika.

@return Wpis dziennika dla odebranej wiadomości. */
char* generate_receive_log(const char *msg) {
    // Sprawdzenie długości wiadomości
    if (msg == NULL || strlen(msg) > MAX_MSG_LEN) {
        return NULL; // Zwróć NULL, jeśli wiadomość jest niepoprawna
    }

    // Bufor na znacznik czasu
    char timestamp[TIMESTAMP_LEN];
    time_t now = time(NULL);
    struct tm *tm_info = localtime(&now);

    // Formatowanie znacznika czasu w formacie ISO
    strftime(timestamp, TIMESTAMP_LEN, "%Y-%m-%dT%H:%M:%S", tm_info);

    // Bufor na wynikowy wpis dziennika
    size_t log_length = strlen(timestamp) + strlen(msg) + 30; // 30 to szacunkowa długość tekstu
    char *log_entry = (char *)malloc(log_length * sizeof(char));
    
    // Sprawdzenie, czy alokacja powiodła się
    if (log_entry == NULL) {
        return NULL; // Zwróć NULL, jeśli nie udało się przydzielić pamięci
    }

    // Tworzenie wpisu dziennika
    snprintf(log_entry, log_length, "[%s] Odebrano: %s", timestamp, msg);

    return log_entry;
}