#include <stdio.h>
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
    // Tarkistetaan että parametrit ovat kelvollisia
    if (info_type == NULL || info_content == NULL || header == NULL) {
        return header;
    }
    
    // Luodaan kopio alkuperäisestä headerista varmuuden vuoksi
    HeaderDict *original_header = malloc(sizeof(HeaderDict));
    if (original_header == NULL) {
        return header;
    }
    memcpy(original_header, header, sizeof(HeaderDict));
    
    // Määritetään otsikkoavain tiedostotyypin perusteella
    char header_key[50] = {0};
    
    if (strcmp(info_type, "lang") == 0) {
        strcpy(header_key, "Accept-Language");
    } else if (strcmp(info_type, "encoding") == 0) {
        strcpy(header_key, "Accept-Encoding");
    } else if (strcmp(info_type, "cache") == 0) {
        strcpy(header_key, "Cache-Control");
    } else {
        // Tuntematon tietotyyppi - palautetaan alkuperäinen
        free(original_header);
        return header;
    }
    
    // Etsitään onko avain jo olemassa
    int existing_index = find_header_index(header, header_key);
    
    if (existing_index != -1) {
        // Päivitetään olemassa oleva arvo
        strncpy(header->entries[existing_index].value, info_content, sizeof(header->entries[existing_index].value) - 1);
        header->entries[existing_index].value[sizeof(header->entries[existing_index].value) - 1] = '\0';
    } else {
        // Lisätään uusi merkintä, jos tilaa on
        if (header->count < HEADER_SIZE) {
            strncpy(header->entries[header->count].key, header_key, sizeof(header->entries[header->count].key) - 1);
            header->entries[header->count].key[sizeof(header->entries[header->count].key) - 1] = '\0';
            
            strncpy(header->entries[header->count].value, info_content, sizeof(header->entries[header->count].value) - 1);
            header->entries[header->count].value[sizeof(header->entries[header->count].value) - 1] = '\0';
            
            header->count++;
        } else {
            // Ei tilaa - palautetaan alkuperäinen
            memcpy(header, original_header, sizeof(HeaderDict));
        }
    }
    
    free(original_header);
    return header;
}