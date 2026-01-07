#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define MAX_MSG_LEN 256
#define TIMESTAMP_LEN 20

/* Luo lokimerkintä vastaanotetulle käyttäjäviestille nykyisellä aikaleimalla muodossa '[<timestamp_iso_format>] Vastaanotettu: <msg>'.
   @param msg Vastaanotettu käyttäjäviesti.
   @return Lokimerkintä vastaanotetulle viestille. */
char* generate_receive_log(const char *msg) {
    // Tarkistetaan, että viestin pituus ei ylitä sallittua maksimia
    if (strlen(msg) > MAX_MSG_LEN) {
        return NULL; // Liian pitkä viesti
    }

    // Aikaleiman luominen
    time_t now = time(NULL);
    struct tm *tm_info = localtime(&now);
    char timestamp[TIMESTAMP_LEN];
    strftime(timestamp, TIMESTAMP_LEN, "%Y-%m-%dT%H:%M:%S", tm_info);

    // Lokimerkin pituuden laskeminen
    size_t log_length = strlen(timestamp) + strlen(msg) + 30; // '[<timestamp>] Vastaanotettu: ' + null-terminointi
    char *log_entry = (char*)malloc(log_length);

    // Varmistetaan, että muisti on varattu onnistuneesti
    if (log_entry == NULL) {
        return NULL; // Muistin varaaminen epäonnistui
    }

    // Lokimerkin rakentaminen
    snprintf(log_entry, log_length, "[%s] Vastaanotettu: %s", timestamp, msg);

    return log_entry; // Palautetaan luotu lokimerkki
}