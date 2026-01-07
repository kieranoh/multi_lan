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
    if (info_type == NULL || info_content == NULL || header == NULL) {
        return header;
    }
    
    const char *key_to_use = NULL;
    
    if (strcmp(info_type, "lang") == 0) {
        key_to_use = "Accept-Language";
    } else if (strcmp(info_type, "encoding") == 0) {
        key_to_use = "Accept-Encoding";
    } else if (strcmp(info_type, "cache") == 0) {
        key_to_use = "Cache-Control";
    } else {
        return header;
    }
    
    int index = find_header_index(header, key_to_use);
    
    if (index != -1) {
        strncpy(header->entries[index].value, info_content, sizeof(header->entries[index].value) - 1);
        header->entries[index].value[sizeof(header->entries[index].value) - 1] = '\0';
    } else {
        if (header->count >= HEADER_SIZE) {
            return header;
        }
        
        strncpy(header->entries[header->count].key, key_to_use, sizeof(header->entries[header->count].key) - 1);
        header->entries[header->count].key[sizeof(header->entries[header->count].key) - 1] = '\0';
        
        strncpy(header->entries[header->count].value, info_content, sizeof(header->entries[header->count].value) - 1);
        header->entries[header->count].value[sizeof(header->entries[header->count].value) - 1] = '\0';
        
        header->count++;
    }
    
    return header;
}