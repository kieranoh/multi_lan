#include <string.h>
#include <stdio.h>

HeaderDict* store_info_in_header(const char *info_type, const char *info_content, HeaderDict *header) {
    // Balidatu sarrerako parametroak
    if (info_type == NULL || info_content == NULL || header == NULL) {
        return header;
    }
    
    // Erabili aldagai lokal bat jatorrizko header mantentzeko
    HeaderDict *result = header;
    
    // Zehaztu info_type-aren arabera gakoa
    const char *key = NULL;
    
    if (strcmp(info_type, "lang") == 0) {
        key = "Accept-Language";
    } else if (strcmp(info_type, "encoding") == 0) {
        key = "Accept-Encoding";
    } else if (strcmp(info_type, "cache") == 0) {
        key = "Cache-Control";
    } else {
        // info_type baliogabea, itzuli jatorrizko header aldaketarik gabe
        return header;
    }
    
    // Bilatu gakoa dagoeneko existitzen den
    int index = find_header_index(header, key);
    
    if (index != -1) {
        // Gakoa existitzen da, eguneratu balioa
        strncpy(header->entries[index].value, info_content, sizeof(header->entries[index].value) - 1);
        header->entries[index].value[sizeof(header->entries[index].value) - 1] = '\0';
    } else {
        // Gako berria, gehitu baldin eta tokia badago
        if (header->count < HEADER_SIZE) {
            strncpy(header->entries[header->count].key, key, sizeof(header->entries[header->count].key) - 1);
            header->entries[header->count].key[sizeof(header->entries[header->count].key) - 1] = '\0';
            
            strncpy(header->entries[header->count].value, info_content, sizeof(header->entries[header->count].value) - 1);
            header->entries[header->count].value[sizeof(header->entries[header->count].value) - 1] = '\0';
            
            header->count++;
        } else {
            // Ez dago tokirik, itzuli jatorrizko header aldaketarik gabe
            return header;
        }
    }
    
    return result;
}