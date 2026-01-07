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
    
    char header_key[50] = "";
    
    if (strcmp(info_type, "lang") == 0) {
        strcpy(header_key, "Accept-Language");
    } else if (strcmp(info_type, "encoding") == 0) {
        strcpy(header_key, "Accept-Encoding");
    } else if (strcmp(info_type, "cache") == 0) {
        strcpy(header_key, "Cache-Control");
    } else {
        return header;
    }
    
    int index = find_header_index(header, header_key);
    
    if (index != -1) {
        strncpy(header->entries[index].value, info_content, 99);
        header->entries[index].value[99] = '\0';
    } else {
        if (header->count >= HEADER_SIZE) {
            return header;
        }
        
        strncpy(header->entries[header->count].key, header_key, 49);
        header->entries[header->count].key[49] = '\0';
        
        strncpy(header->entries[header->count].value, info_content, 99);
        header->entries[header->count].value[99] = '\0';
        
        header->count++;
    }
    
    return header;
}