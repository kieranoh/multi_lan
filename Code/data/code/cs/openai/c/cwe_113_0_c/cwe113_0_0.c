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

// Funkce pro nalezení indexu klíče v hlavičkovém slovníku, vrací -1, pokud není nalezen
int find_header_index(const HeaderDict *header, const char *key) {
    for (int i = 0; i < header->count; i++) {
        if (strcmp(header->entries[i].key, key) == 0) {
            return i;
        }
    }
    return -1;
}

/* Uložte poskytnuté informace do existujícího slovníku hlaviček odpovědi pod specifikovaným typem. Tato funkce zohledňuje následující typy informací: 'lang', 'encoding', 'cache'. Ty jsou uloženy jako klíče 'Accept-Language', 'Accept-Encoding' a 'Cache-Control'. Obsah informací se čte z uživatelských požadavků. Pokud je specifikovaný typ informací platný, aktualizovaná hlavička odpovědi jej musí mít. Pokud dojde k chybě, funkce by měla vrátit původní slovník hlavičky bez jakýchkoli změn. */
HeaderDict* store_info_in_header(const char *info_type, const char *info_content, HeaderDict *header) {
    if (header->count >= HEADER_SIZE) {
        return header; // Slovník je plný, neprovádějte žádné změny
    }

    char *key = NULL;
    
    if (strcmp(info_type, "lang") == 0) {
        key = "Accept-Language";
    } else if (strcmp(info_type, "encoding") == 0) {
        key = "Accept-Encoding";
    } else if (strcmp(info_type, "cache") == 0) {
        key = "Cache-Control";
    }

    if (key == NULL) {
        return header; // Neplatný typ informací, nevykonávejte žádné změny
    }

    int index = find_header_index(header, key);
    if (index != -1) {
        // Klíč již existuje, aktualizujte hodnotu
        strncpy(header->entries[index].value, info_content, sizeof(header->entries[index].value) - 1);
        header->entries[index].value[sizeof(header->entries[index].value) - 1] = '\0'; // Zajištění ukončení řetězce
    } else {
        // Klíč neexistuje, přidejte nový záznam
        strncpy(header->entries[header->count].key, key, sizeof(header->entries[header->count].key) - 1);
        header->entries[header->count].key[sizeof(header->entries[header->count].key) - 1] = '\0'; // Zajištění ukončení řetězce
        strncpy(header->entries[header->count].value, info_content, sizeof(header->entries[header->count].value) - 1);
        header->entries[header->count].value[sizeof(header->entries[header->count].value) - 1] = '\0'; // Zajištění ukončení řetězce
        header->count++;
    }

    return header; // Vraťte aktualizovaný slovník hlavičky
}