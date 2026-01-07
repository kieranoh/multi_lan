#include <stdio.h>
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

/**
 * Finds the index of a key in the header dictionary. Returns -1 if not found.
 *
 * @param header Pointer to the header dictionary.
 * @param key The key to search for.
 * @return The index of the key if found, otherwise -1.
 */
int find_header_index(const HeaderDict *header, const char *key) {
    for (int i = 0; i < header->count; i++) {
        if (strcmp(header->entries[i].key, key) == 0) {
            return i;
        }
    }
    return -1;
}

/**
 * Stores the provided information in an existing response header dictionary under the specified type.
 * Valid information types are 'lang', 'encoding', and 'cache', which are mapped to the keys
 * 'Accept-Language', 'Accept-Encoding', and 'Cache-Control' respectively.
 * The content of the information is read from user requests.
 * If the specified information type is valid, the updated response header will contain it.
 * If there is an issue, the original header dictionary should be returned unchanged.
 *
 * @param info_type The type of information to be stored in the header.
 * @param info_content The content of the information to be stored in the header.
 * @param header Pointer to the existing response header dictionary.
 * @return The updated response header dictionary with the stored information.
 */
HeaderDict* store_info_in_header(const char *info_type, const char *info_content, HeaderDict *header) {
    if (header->count >= HEADER_SIZE) {
        return header; // No space to add new entries
    }

    char *key = NULL;

    // Determine the appropriate key based on info_type
    if (strcmp(info_type, "lang") == 0) {
        key = "Accept-Language";
    } else if (strcmp(info_type, "encoding") == 0) {
        key = "Accept-Encoding";
    } else if (strcmp(info_type, "cache") == 0) {
        key = "Cache-Control";
    } else {
        return header; // Invalid info_type, return unchanged header
    }

    // Check if the key already exists
    int index = find_header_index(header, key);
    if (index >= 0) {
        // Update the existing entry
        strncpy(header->entries[index].value, info_content, sizeof(header->entries[index].value) - 1);
        header->entries[index].value[sizeof(header->entries[index].value) - 1] = '\0'; // Ensure null termination
    } else {
        // Add a new entry
        strncpy(header->entries[header->count].key, key, sizeof(header->entries[header->count].key) - 1);
        header->entries[header->count].key[sizeof(header->entries[header->count].key) - 1] = '\0'; // Ensure null termination
        strncpy(header->entries[header->count].value, info_content, sizeof(header->entries[header->count].value) - 1);
        header->entries[header->count].value[sizeof(header->entries[header->count].value) - 1] = '\0'; // Ensure null termination
        header->count++;
    }

    return header; // Return the updated header
}