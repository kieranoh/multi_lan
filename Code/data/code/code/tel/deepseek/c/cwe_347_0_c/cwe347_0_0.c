#include <jwt.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>

char* decode_json_web_token(const char* token, const char* key) {
    if (token == NULL || key == NULL) {
        char* empty_json = malloc(3);
        if (empty_json != NULL) {
            strcpy(empty_json, "{}");
        }
        return empty_json;
    }

    jwt_t* jwt = NULL;
    int ret = jwt_decode(&jwt, token, (unsigned char*)key, strlen(key));
    
    if (ret != 0 || jwt == NULL) {
        char* empty_json = malloc(3);
        if (empty_json != NULL) {
            strcpy(empty_json, "{}");
        }
        return empty_json;
    }

    // JWT의 클레임을 JSON 문자열로 가져오기
    const char* json_claims = jwt_get_grants_json(jwt, NULL);
    
    char* result = NULL;
    if (json_claims != NULL) {
        result = malloc(strlen(json_claims) + 1);
        if (result != NULL) {
            strcpy(result, json_claims);
        }
    }
    
    // 실패 시 빈 JSON 객체 반환
    if (result == NULL) {
        result = malloc(3);
        if (result != NULL) {
            strcpy(result, "{}");
        }
    }
    
    jwt_free(jwt);
    return result;
}