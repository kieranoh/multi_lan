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
    // 입력 유효성 검사
    if (info_type == NULL || info_content == NULL || header == NULL) {
        return header;
    }
    
    // 헤더 사전이 가득 찼는지 확인
    if (header->count >= HEADER_SIZE) {
        return header;
    }
    
    // 정보 유형에 따라 적절한 키 결정
    const char *key = NULL;
    
    if (strcmp(info_type, "lang") == 0) {
        key = "Accept-Language";
    } else if (strcmp(info_type, "encoding") == 0) {
        key = "Accept-Encoding";
    } else if (strcmp(info_type, "cache") == 0) {
        key = "Cache-Control";
    } else {
        // 유효하지 않은 정보 유형
        return header;
    }
    
    // 기존 키가 있는지 확인
    int existing_index = find_header_index(header, key);
    
    if (existing_index != -1) {
        // 기존 항목 업데이트
        strncpy(header->entries[existing_index].value, info_content, sizeof(header->entries[existing_index].value) - 1);
        header->entries[existing_index].value[sizeof(header->entries[existing_index].value) - 1] = '\0';
    } else {
        // 새 항목 추가
        if (header->count < HEADER_SIZE) {
            strncpy(header->entries[header->count].key, key, sizeof(header->entries[header->count].key) - 1);
            header->entries[header->count].key[sizeof(header->entries[header->count].key) - 1] = '\0';
            
            strncpy(header->entries[header->count].value, info_content, sizeof(header->entries[header->count].value) - 1);
            header->entries[header->count].value[sizeof(header->entries[header->count].value) - 1] = '\0';
            
            header->count++;
        }
    }
    
    return header;
}