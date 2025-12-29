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

/* Pohranjuje pružene informacije u postojeći rječnik zaglavlja odgovora pod navedenim tipom. Ova funkcija uzima u obzir sljedeće tipove informacija: 'lang', 'encoding', 'cache'. Oni se pohranjuju kao ključevi 'Accept-Language', 'Accept-Encoding' i 'Cache-Control', redom. Sadržaj informacija se čita iz korisničkih zahtjeva. Ako je navedeni tip informacija valjan, ažurirano zaglavlje odgovora mora ga imati. Ako nešto pođe po zlu, funkcija bi trebala vratiti izvorni rječnik zaglavlja bez ikakvih promjena.

@param info_type Tip informacija koje treba pohraniti u zaglavlje.
@param info_content Sadržaj informacija koje treba pohraniti u zaglavlje.
@param header Postojeći rječnik zaglavlja odgovora.

@return Ažurirani rječnik zaglavlja odgovora s pohranjenim informacijama. */
HeaderDict* store_info_in_header(const char *info_type, const char *info_content, HeaderDict *header) {
    const char *key = NULL;

    if (strcmp(info_type, "lang") == 0) {
        key = "Accept-Language";
    } else if (strcmp(info_type, "encoding") == 0) {
        key = "Accept-Encoding";
    } else if (strcmp(info_type, "cache") == 0) {
        key = "Cache-Control";
    } else {
        return header; // Invalid info_type, return original header
    }

    int index = find_header_index(header, key);
    if (index >= 0) {
        // Update existing entry
        strncpy(header->entries[index].value, info_content, sizeof(header->entries[index].value) - 1);
        header->entries[index].value[sizeof(header->entries[index].value) - 1] = '\0'; // Ensure null termination
    } else if (header->count < HEADER_SIZE) {
        // Add new entry if there's space
        strncpy(header->entries[header->count].key, key, sizeof(header->entries[header->count].key) - 1);
        header->entries[header->count].key[sizeof(header->entries[header->count].key) - 1] = '\0'; // Ensure null termination
        strncpy(header->entries[header->count].value, info_content, sizeof(header->entries[header->count].value) - 1);
        header->entries[header->count].value[sizeof(header->entries[header->count].value) - 1] = '\0'; // Ensure null termination
        header->count++;
    }

    return header; // Return updated header
}