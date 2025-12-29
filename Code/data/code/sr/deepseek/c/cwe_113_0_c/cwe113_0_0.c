#include <string.h>
#include <stdlib.h>

#define HEADER_SIZE 10

typedef struct {
    char key[50];
    char value[100];
} HeaderEntry;

typedef struct {
    HeaderEntry entries[HEADER_SIZE];
    int count;
} HeaderDict;

int find_header_index(const HeaderDict *header, const char *key) {
    for (int i = 0; i < header->count; i++) {
        if (strcmp(header->entries[i].key, key) == 0) {
            return i;
        }
    }
    return -1;
}

HeaderDict* store_info_in_header(const char *info_type, const char *info_content, HeaderDict *header) {
    // Provera validnosti ulaznih parametara
    if (info_type == NULL || info_content == NULL || header == NULL) {
        return header;
    }
    
    // Provera da li ima mesta u rečniku ako treba dodati novi unos
    int index = -1;
    const char *header_key = NULL;
    
    // Mapiranje tipa informacija na odgovarajući ključ zaglavlja
    if (strcmp(info_type, "lang") == 0) {
        header_key = "Accept-Language";
    } else if (strcmp(info_type, "encoding") == 0) {
        header_key = "Accept-Encoding";
    } else if (strcmp(info_type, "cache") == 0) {
        header_key = "Cache-Control";
    } else {
        // Nevalidan tip informacija - vrati originalni rečnik bez promena
        return header;
    }
    
    // Pronađi indeks ako ključ već postoji
    index = find_header_index(header, header_key);
    
    if (index != -1) {
        // Ključ već postoji - ažuriraj vrednost
        strncpy(header->entries[index].value, info_content, sizeof(header->entries[index].value) - 1);
        header->entries[index].value[sizeof(header->entries[index].value) - 1] = '\0';
    } else {
        // Ključ ne postoji - dodaj novi unos
        if (header->count >= HEADER_SIZE) {
            // Nema mesta - vrati originalni rečnik bez promena
            return header;
        }
        
        strncpy(header->entries[header->count].key, header_key, sizeof(header->entries[header->count].key) - 1);
        header->entries[header->count].key[sizeof(header->entries[header->count].key) - 1] = '\0';
        
        strncpy(header->entries[header->count].value, info_content, sizeof(header->entries[header->count].value) - 1);
        header->entries[header->count].value[sizeof(header->entries[header->count].value) - 1] = '\0';
        
        header->count++;
    }
    
    return header;
}