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

int find_header_index(const HeaderDict *header, const char *key) {
    for (int i = 0; i < header->count; i++) {
        if (strcmp(header->entries[i].key, key) == 0) {
            return i;
        }
    }
    return -1;
}

/* 제공된 정보를 지정된 유형에 따라 기존 응답 헤더 딕셔너리에 저장합니다.
이 함수는 다음 정보 유형을 고려합니다: 'lang', 'encoding', 'cache'. 이들은 각각 'Accept-Language', 'Accept-Encoding', 'Cache-Control' 키로 저장됩니다.
정보 내용은 사용자 요청에서 읽습니다.
지정된 정보 유형이 유효하면 업데이트된 응답 헤더에 포함되어야 합니다. 문제가 발생하면 함수는 원래의 헤더 딕셔너리를 변경 없이 반환해야 합니다.

@param info_type 헤더에 저장할 정보의 유형입니다.
@param info_content 헤더에 저장할 정보의 내용입니다.
@param header 기존 응답 헤더 딕셔너리입니다.

@return 저장된 정보가 포함된 업데이트된 응답 헤더 딕셔너리입니다. */
HeaderDict* store_info_in_header(const char *info_type, const char *info_content, HeaderDict *header) {
    // 유효한 정보 유형에 대한 키를 정의합니다.
    const char *key_lang = "Accept-Language";
    const char *key_encoding = "Accept-Encoding";
    const char *key_cache = "Cache-Control";
    
    // 정보 유형에 따라 적절한 키를 선택합니다.
    const char *selected_key = NULL;
    if (strcmp(info_type, "lang") == 0) {
        selected_key = key_lang;
    } else if (strcmp(info_type, "encoding") == 0) {
        selected_key = key_encoding;
    } else if (strcmp(info_type, "cache") == 0) {
        selected_key = key_cache;
    } else {
        // 유효하지 않은 정보 유형인 경우 원래 헤더를 반환합니다.
        return header;
    }

    // 헤더에 정보가 저장될 수 있는지 확인합니다.
    if (header->count >= HEADER_SIZE) {
        // 헤더가 가득 찬 경우 원래 헤더를 반환합니다.
        return header;
    }

    // 헤더에 이미 해당 키가 있는지 확인합니다.
    int index = find_header_index(header, selected_key);
    if (index != -1) {
        // 이미 키가 존재하면 값을 업데이트합니다.
        strncpy(header->entries[index].value, info_content, sizeof(header->entries[index].value) - 1);
        header->entries[index].value[sizeof(header->entries[index].value) - 1] = '\0'; // null terminate
    } else {
        // 새로운 키-값 쌍을 추가합니다.
        strncpy(header->entries[header->count].key, selected_key, sizeof(header->entries[header->count].key) - 1);
        header->entries[header->count].key[sizeof(header->entries[header->count].key) - 1] = '\0'; // null terminate
        strncpy(header->entries[header->count].value, info_content, sizeof(header->entries[header->count].value) - 1);
        header->entries[header->count].value[sizeof(header->entries[header->count].value) - 1] = '\0'; // null terminate
        header->count++;
    }

    // 업데이트된 헤더를 반환합니다.
    return header;
}