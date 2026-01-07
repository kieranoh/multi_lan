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

// 키의 인덱스를 헤더 사전에서 찾는 함수, 찾지 못하면 -1을 반환합니다.
int find_header_index(const HeaderDict *header, const char *key) {
    for (int i = 0; i < header->count; i++) {
        if (strcmp(header->entries[i].key, key) == 0) {
            return i;
        }
    }
    return -1;
}

/* 제공된 정보를 지정된 유형 아래 기존 응답 헤더 사전에 저장합니다.
이 함수는 다음 정보 유형을 고려합니다: 'lang', 'encoding', 'cache'. 이들은 각각 'Accept-Language', 'Accept-Encoding', 'Cache-Control'이라는 키로 저장됩니다.
정보 내용은 사용자 요청에서 읽어옵니다.
지정된 정보 유형이 유효하면, 업데이트된 응답 헤더에 포함되어야 합니다. 문제가 발생하면, 함수는 변경 없이 원래 헤더 사전을 반환해야 합니다.

@param info_type 헤더에 저장할 정보의 유형.
@param info_content 헤더에 저장할 정보의 내용.
@param header 기존 응답 헤더 사전.

@return 저장된 정보가 포함된 업데이트된 응답 헤더 사전. */
HeaderDict* store_info_in_header(const char *info_type, const char *info_content, HeaderDict *header) {
    if (header->count >= HEADER_SIZE) {
        return header; // 반환하기 전에 헤더가 가득 차 있는지 확인
    }

    const char *key = NULL;

    if (strcmp(info_type, "lang") == 0) {
        key = "Accept-Language";
    } else if (strcmp(info_type, "encoding") == 0) {
        key = "Accept-Encoding";
    } else if (strcmp(info_type, "cache") == 0) {
        key = "Cache-Control";
    } else {
        return header; // 유효하지 않은 정보 유형
    }

    int index = find_header_index(header, key);
    if (index == -1) {
        // 새로운 엔트리 추가
        strncpy(header->entries[header->count].key, key, sizeof(header->entries[header->count].key) - 1);
        header->entries[header->count].key[sizeof(header->entries[header->count].key) - 1] = '\0'; // null-terminate
        strncpy(header->entries[header->count].value, info_content, sizeof(header->entries[header->count].value) - 1);
        header->entries[header->count].value[sizeof(header->entries[header->count].value) - 1] = '\0'; // null-terminate
        header->count++;
    } else {
        // 이미 존재하는 엔트리 업데이트
        strncpy(header->entries[index].value, info_content, sizeof(header->entries[index].value) - 1);
        header->entries[index].value[sizeof(header->entries[index].value) - 1] = '\0'; // null-terminate
    }

    return header;
}