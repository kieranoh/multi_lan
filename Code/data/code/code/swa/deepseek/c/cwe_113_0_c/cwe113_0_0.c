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

// 키의 인덱스를 헤더 딕셔너리에서 찾는 함수, 찾지 못하면 -1을 반환합니다.
int find_header_index(const HeaderDict *header, const char *key) {
    for (int i = 0; i < header->count; i++) {
        if (strcmp(header->entries[i].key, key) == 0) {
            return i;
        }
    }
    return -1;
}

/* 제공된 정보를 지정된 유형 아래 기존 응답 헤더 딕셔너리에 저장합니다. 이 함수는 다음 정보 유형을 고려합니다: 'lang', 'encoding', 'cache'. 이들은 각각 'Accept-Language', 'Accept-Encoding', 'Cache-Control' 키로 저장됩니다. 정보 내용은 사용자 요청에서 읽습니다. 지정된 정보 유형이 유효하면, 업데이트된 응답 헤더에 포함되어야 합니다. 문제가 발생하면, 함수는 변경 없이 원래 헤더 딕셔너리를 반환해야 합니다.

@param info_type 헤더에 저장할 정보의 유형.
@param info_content 헤더에 저장할 정보의 내용.
@param header 기존 응답 헤더 딕셔너리.

@return 저장된 정보가 포함된 업데이트된 응답 헤더 딕셔너리. */
HeaderDict* store_info_in_header(const char *info_type, const char *info_content, HeaderDict *header) {
    // 유효성 검사: NULL 포인터 확인
    if (info_type == NULL || info_content == NULL || header == NULL) {
        return header;
    }
    
    // 헤더 딕셔너리가 가득 찼는지 확인
    if (header->count >= HEADER_SIZE) {
        return header;
    }
    
    // info_type에 따른 실제 헤더 키 결정
    const char *header_key = NULL;
    
    if (strcmp(info_type, "lang") == 0) {
        header_key = "Accept-Language";
    } else if (strcmp(info_type, "encoding") == 0) {
        header_key = "Accept-Encoding";
    } else if (strcmp(info_type, "cache") == 0) {
        header_key = "Cache-Control";
    } else {
        // 유효하지 않은 info_type인 경우 원래 헤더 반환
        return header;
    }
    
    // info_content의 길이 검사 (저장 가능한 최대 길이보다 작아야 함)
    if (strlen(info_content) >= 100) {
        return header;
    }
    
    // 이미 존재하는 키인지 확인
    int existing_index = find_header_index(header, header_key);
    
    if (existing_index != -1) {
        // 기존 항목 업데이트
        strncpy(header->entries[existing_index].value, info_content, 99);
        header->entries[existing_index].value[99] = '\0'; // 안전한 종료
    } else {
        // 새 항목 추가
        strncpy(header->entries[header->count].key, header_key, 49);
        header->entries[header->count].key[49] = '\0'; // 안전한 종료
        
        strncpy(header->entries[header->count].value, info_content, 99);
        header->entries[header->count].value[99] = '\0'; // 안전한 종료
        
        header->count++;
    }
    
    return header;
}