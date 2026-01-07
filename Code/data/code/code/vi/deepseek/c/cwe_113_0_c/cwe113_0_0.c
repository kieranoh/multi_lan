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
    // Validate input parameters
    if (info_type == NULL || info_content == NULL || header == NULL) {
        return header;
    }
    
    // Check if header is full
    if (header->count >= HEADER_SIZE) {
        return header;
    }
    
    char header_key[50] = "";
    int valid_type = 1;
    
    // Determine the header key based on info_type
    if (strcmp(info_type, "lang") == 0) {
        strcpy(header_key, "Accept-Language");
    } else if (strcmp(info_type, "encoding") == 0) {
        strcpy(header_key, "Accept-Encoding");
    } else if (strcmp(info_type, "cache") == 0) {
        strcpy(header_key, "Cache-Control");
    } else {
        valid_type = 0;
    }
    
    // If info_type is not valid, return original header unchanged
    if (!valid_type) {
        return header;
    }
    
    // Check if the key already exists
    int existing_index = find_header_index(header, header_key);
    
    if (existing_index != -1) {
        // Update existing entry
        strncpy(header->entries[existing_index].value, info_content, 99);
        header->entries[existing_index].value[99] = '\0';
    } else {
        // Add new entry
        strncpy(header->entries[header->count].key, header_key, 49);
        header->entries[header->count].key[49] = '\0';
        
        strncpy(header->entries[header->count].value, info_content, 99);
        header->entries[header->count].value[99] = '\0';
        
        header->count++;
    }
    
    return header;
}