#include <jwt.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>

char* decode_json_web_token(const char* token, const char* key) {
    jwt_t *jwt = NULL;
    char *result = NULL;
    
    // 토큰이나 키가 NULL인 경우 빈 JSON 객체 반환
    if (token == NULL || key == NULL) {
        result = malloc(3);
        if (result != NULL) {
            strcpy(result, "{}");
        }
        return result;
    }
    
    // JWT 디코딩 시도
    int ret = jwt_decode(&jwt, token, (unsigned char*)key, strlen(key));
    
    if (ret != 0 || jwt == NULL) {
        // 디코딩 실패 시 빈 JSON 객체 반환
        result = malloc(3);
        if (result != NULL) {
            strcpy(result, "{}");
        }
        return result;
    }
    
    // JWT에서 클레임을 JSON 문자열로 가져오기
    const char *json_str = jwt_get_grants_json(jwt, NULL);
    
    if (json_str == NULL) {
        // JSON 문자열 가져오기 실패 시 빈 JSON 객체 반환
        result = malloc(3);
        if (result != NULL) {
            strcpy(result, "{}");
        }
    } else {
        // 성공 시 JSON 문자열 복사
        result = malloc(strlen(json_str) + 1);
        if (result != NULL) {
            strcpy(result, json_str);
        } else {
            // 메모리 할당 실패 시 빈 JSON 객체 반환
            result = malloc(3);
            if (result != NULL) {
                strcpy(result, "{}");
            }
        }
    }
    
    // JWT 객체 정리
    jwt_free(jwt);
    
    return result;
}