#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define MAX_MSG_LEN 256

/* Luo lokimerkintä vastaanotetulle käyttäjäviestille nykyisellä aikaleimalla muodossa '[<timestamp_iso_format>] Vastaanotettu: <msg>'.

@param msg Vastaanotettu käyttäjäviestille.
@return Lokimerkintä vastaanotetulle viestille. */
char* generate_receive_log(const char *msg) {
    // Tarkista että viesti ei ole NULL ja että se mahtuu maksimipituuteen
    if (msg == NULL) {
        return NULL;
    }
    
    // Hae nykyinen aika
    time_t rawtime;
    struct tm *timeinfo;
    char timestamp[20]; // YYYY-MM-DD HH:MM:SS + null-terminator
    
    time(&rawtime);
    timeinfo = localtime(&rawtime);
    
    // Muotoile aikaleima ISO-muotoon (YYYY-MM-DD HH:MM:SS)
    strftime(timestamp, sizeof(timestamp), "%Y-%m-%d %H:%M:%S", timeinfo);
    
    // Laske tarvittavan muistin määrä
    // [timestamp] Vastaanotettu: msg\0
    size_t msg_len = strlen(msg);
    size_t log_len = 2 + strlen(timestamp) + 2 + 12 + 2 + msg_len + 1; // [] + timestamp + "] " + "Vastaanotettu: " + ": " + msg + \0
    
    // Varmista että viesti ei ylitä maksimipituutta
    if (msg_len > MAX_MSG_LEN) {
        return NULL;
    }
    
    // Varaa muisti lokimerkinnälle
    char *log_entry = (char*)malloc(log_len);
    if (log_entry == NULL) {
        return NULL;
    }
    
    // Muodosta lokimerkintä
    snprintf(log_entry, log_len, "[%s] Vastaanotettu: %s", timestamp, msg);
    
    return log_entry;
}