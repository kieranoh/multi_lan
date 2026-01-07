#include <string.h>
#include <stdlib.h>

HeaderDict* store_info_in_header(const char *info_type, const char *info_content, HeaderDict *header) {
    // Check for NULL pointers
    if (info_type == NULL || info_content == NULL || header == NULL) {
        return header;
    }
    
    // Determine the key based on info_type
    const char *key = NULL;
    
    if (strcmp(info_type, "lang") == 0) {
        key = "Accept-Language";
    } else if (strcmp(info_type, "encoding") == 0) {
        key = "Accept-Encoding";
    } else if (strcmp(info_type, "cache") == 0) {
        key = "Cache-Control";
    } else {
        // Invalid info_type, return original header unchanged
        return header;
    }
    
    // Check if header dictionary is full
    if (header->count >= HEADER_SIZE) {
        return header;
    }
    
    // Find if the key already exists
    int index = find_header_index(header, key);
    
    if (index != -1) {
        // Key exists, update the value
        strncpy(header->entries[index].value, info_content, sizeof(header->entries[index].value) - 1);
        header->entries[index].value[sizeof(header->entries[index].value) - 1] = '\0';
    } else {
        // Key doesn't exist, add new entry
        strncpy(header->entries[header->count].key, key, sizeof(header->entries[header->count].key) - 1);
        header->entries[header->count].key[sizeof(header->entries[header->count].key) - 1] = '\0';
        
        strncpy(header->entries[header->count].value, info_content, sizeof(header->entries[header->count].value) - 1);
        header->entries[header->count].value[sizeof(header->entries[header->count].value) - 1] = '\0';
        
        header->count++;
    }
    
    return header;
}