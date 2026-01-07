#include <jwt.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>

char* decode_json_web_token(const char* token, const char* key) {
    // 입력 검증
    if (token == NULL || key == NULL || strlen(token) == 0 || strlen(key) == 0) {
        char* empty_json = malloc(3);
        if (empty_json != NULL) {
            strcpy(empty_json, "{}");
        }
        return empty_json;
    }
    
    jwt_t* jwt = NULL;
    char* result = NULL;
    
    // JWT 디코딩 시도
    int ret = jwt_decode(&jwt, token, (unsigned char*)key, strlen(key));
    
    if (ret == 0 && jwt != NULL) {
        // JWT에서 클레임을 JSON 형식으로 가져오기
        const char* json_claims = jwt_get_grants_json(jwt, NULL);
        
        if (json_claims != NULL) {
            // 결과 문자열 복사
            result = malloc(strlen(json_claims) + 1);
            if (result != NULL) {
                strcpy(result, json_claims);
            }
        } else {
            // JSON 클레임을 가져오지 못한 경우 빈 JSON 객체 반환
            result = malloc(3);
            if (result != NULL) {
                strcpy(result, "{}");
            }
        }
        
        // JWT 객체 정리
        jwt_free(jwt);
    } else {
        // 디코딩 실패 시 빈 JSON 객체 반환
        result = malloc(3);
        if (result != NULL) {
            strcpy(result, "{}");
        }
    }
    
    // 메모리 할당 실패 시 빈 JSON 객체 반환
    if (result == NULL) {
        result = malloc(3);
        if (result != NULL) {
            strcpy(result, "{}");
        }
    }
    
    return result;
}