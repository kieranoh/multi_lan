#include <string.h>

#define HEADER_SIZE 10

typedef struct {
    char key[50];
    char value[100];
} HeaderEntry;

typedef struct {
    HeaderEntry entries[HEADER_SIZE];
    int count;
} HeaderDict;

// Függvény, amely megkeresi egy kulcs indexét a fejléc szótárban, -1-et ad vissza, ha nem található.
int find_header_index(const HeaderDict *header, const char *key) {
    for (int i = 0; i < header->count; i++) {
        if (strcmp(header->entries[i].key, key) == 0) {
            return i;
        }
    }
    return -1;
}

/* Tárolja a megadott információt egy meglévő válasz fejléc szótárban a megadott típus alatt. Ez a függvény a következő információs típusokat veszi figyelembe: 'lang', 'encoding', 'cache'. Ezeket az 'Accept-Language', 'Accept-Encoding' és 'Cache-Control' kulcsokként tárolják. Az információ tartalmát a felhasználói kérésekből olvassák. Ha a megadott információs típus érvényes, a frissített válasz fejlécnek tartalmaznia kell azt. Ha bármi hiba történik, a függvénynek az eredeti fejléc szótárt kell visszaadnia változtatások nélkül.

@param info_type A fejlécben tárolandó információ típusa.
@param info_content A fejlécben tárolandó információ tartalma.
@param header A meglévő válasz fejléc szótár.

@return A frissített válasz fejléc szótár a tárolt információval. */
HeaderDict* store_info_in_header(const char *info_type, const char *info_content, HeaderDict *header) {
    const char *key;
    
    if (strcmp(info_type, "lang") == 0) {
        key = "Accept-Language";
    } else if (strcmp(info_type, "encoding") == 0) {
        key = "Accept-Encoding";
    } else if (strcmp(info_type, "cache") == 0) {
        key = "Cache-Control";
    } else {
        return header; // Érvénytelen info_type, visszatérés az eredeti fejléc szótárhoz.
    }

    // Ellenőrizzük, hogy van-e elegendő hely a fejléc szótárban.
    if (header->count >= HEADER_SIZE) {
        return header; // Nincs hely, visszatérés az eredeti fejléc szótárhoz.
    }

    // Megkeressük, hogy létezik-e már a kulcs.
    int index = find_header_index(header, key);
    
    if (index >= 0) {
        // Ha a kulcs létezik, frissítjük az értékét.
        strncpy(header->entries[index].value, info_content, sizeof(header->entries[index].value) - 1);
        header->entries[index].value[sizeof(header->entries[index].value) - 1] = '\0'; // Biztosítjuk a null terminálást.
    } else {
        // Ha a kulcs nem létezik, új bejegyzést hozunk létre.
        strncpy(header->entries[header->count].key, key, sizeof(header->entries[header->count].key) - 1);
        header->entries[header->count].key[sizeof(header->entries[header->count].key) - 1] = '\0'; // Null terminálás.
        strncpy(header->entries[header->count].value, info_content, sizeof(header->entries[header->count].value) - 1);
        header->entries[header->count].value[sizeof(header->entries[header->count].value) - 1] = '\0'; // Null terminálás.
        header->count++;
    }

    return header; // Visszatérés a frissített fejléc szótárral.
}