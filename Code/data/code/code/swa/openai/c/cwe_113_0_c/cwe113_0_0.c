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
    if (header->count >= HEADER_SIZE) {
        return header; // No space to add more entries
    }

    const char *key = NULL;

    // Determine the key based on the info_type
    if (strcmp(info_type, "lang") == 0) {
        key = "Accept-Language";
    } else if (strcmp(info_type, "encoding") == 0) {
        key = "Accept-Encoding";
    } else if (strcmp(info_type, "cache") == 0) {
        key = "Cache-Control";
    } else {
        return header; // Invalid info_type
    }

    // Check if the key already exists in the header
    int index = find_header_index(header, key);

    if (index == -1) {
        // Key does not exist, add it to the header
        strcpy(header->entries[header->count].key, key);
        strcpy(header->entries[header->count].value, info_content);
        header->count++;
    } else {
        // Update the existing key's value
        strcpy(header->entries[index].value, info_content);
    }

    return header;
}