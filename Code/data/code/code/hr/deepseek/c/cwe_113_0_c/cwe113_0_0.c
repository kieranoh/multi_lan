#include <string.h>
#include <stdio.h>

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
    // Provjera ulaznih parametara
    if (info_type == NULL || info_content == NULL || header == NULL) {
        return header;
    }
    
    // Stvaramo kopiju originalnog headera za slučaj greške
    HeaderDict original_header = *header;
    
    // Određujemo ključ zaglavlja na temelju tipa informacija
    const char *header_key = NULL;
    
    if (strcmp(info_type, "lang") == 0) {
        header_key = "Accept-Language";
    } else if (strcmp(info_type, "encoding") == 0) {
        header_key = "Accept-Encoding";
    } else if (strcmp(info_type, "cache") == 0) {
        header_key = "Cache-Control";
    } else {
        // Nepoznati tip informacija - vraćamo originalni header
        return header;
    }
    
    // Provjeravamo je li info_content prazan string
    if (strlen(info_content) == 0) {
        return header;
    }
    
    // Provjeravamo je li header_key predugačak za našu strukturu
    if (strlen(header_key) >= 50) {
        *header = original_header;
        return header;
    }
    
    // Provjeravamo je li info_content predugačak za našu strukturu
    if (strlen(info_content) >= 100) {
        *header = original_header;
        return header;
    }
    
    // Tražimo postoji li već ovaj ključ u headeru
    int existing_index = find_header_index(header, header_key);
    
    if (existing_index != -1) {
        // Ključ već postoji - ažuriramo vrijednost
        strncpy(header->entries[existing_index].value, info_content, 99);
        header->entries[existing_index].value[99] = '\0';
    } else {
        // Ključ ne postoji - dodajemo novi unos
        if (header->count >= HEADER_SIZE) {
            // Nema više mjesta u headeru - vraćamo originalni header
            *header = original_header;
            return header;
        }
        
        // Dodajemo novi unos
        strncpy(header->entries[header->count].key, header_key, 49);
        header->entries[header->count].key[49] = '\0';
        
        strncpy(header->entries[header->count].value, info_content, 99);
        header->entries[header->count].value[99] = '\0';
        
        header->count++;
    }
    
    return header;
}