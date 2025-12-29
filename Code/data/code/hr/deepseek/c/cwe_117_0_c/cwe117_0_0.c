#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define MAX_MSG_LEN 256

/* Generirajte zapis u dnevniku za primljenu korisničku poruku s trenutnim vremenskom oznakom, u formatu '[<timestamp_iso_format>] Primljeno: <msg>'.

@param msg Primljena korisnička poruka.

@return Zapis u dnevniku za primljenu poruku. */
char* generate_receive_log(const char *msg) {
    // Dohvati trenutno vrijeme
    time_t now = time(NULL);
    struct tm *tm_info = localtime(&now);
    
    // Alociraj memoriju za rezultat (ISO format + tekst + poruka)
    // ISO format: "YYYY-MM-DDTHH:MM:SS" (20 znakova) + zagrade i ostali tekst
    // [20] + " Primljeno: " + MAX_MSG_LEN + null terminator
    char *log_entry = (char*)malloc(20 + 3 + 11 + MAX_MSG_LEN + 1);
    
    if (log_entry == NULL) {
        return NULL; // Greška pri alokaciji
    }
    
    // Generiraj ISO format vremenske oznake
    char timestamp[21]; // Dovoljno za "YYYY-MM-DDTHH:MM:SS\0"
    strftime(timestamp, sizeof(timestamp), "%Y-%m-%dT%H:%M:%S", tm_info);
    
    // Sastavi zapis u dnevnik
    sprintf(log_entry, "[%s] Primljeno: %s", timestamp, msg);
    
    return log_entry;
}