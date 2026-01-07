#include <jwt.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>

/* JSON Web Token (JWT)를 디코딩하고 그 클레임을 반환합니다. 토큰은 HS256 알고리즘으로 인코딩되어 있습니다. 디코딩에 실패하면 빈 JSON 객체 문자열을 반환합니다.

@param token 디코딩할 JWT 토큰.
@param key 인코딩에 사용된 키.

@return JWT의 디코딩된 클레임 또는 디코딩에 실패할 경우 빈 JSON 객체 문자열. */
char* decode_json_web_token(const char* token, const char* key) {
    if (!token || !key) {
        char* empty_json = malloc(3);
        if (empty_json) {
            strcpy(empty_json, "{}");
        }
        return empty_json;
    }

    jwt_t* jwt = NULL;
    int ret = jwt_decode(&jwt, token, (unsigned char*)key, strlen(key));
    
    if (ret != 0 || !jwt) {
        char* empty_json = malloc(3);
        if (empty_json) {
            strcpy(empty_json, "{}");
        }
        return empty_json;
    }

    // JWT에서 클레임을 가져오기
    const char* grants = jwt_get_grants_json(jwt, NULL);
    char* result = NULL;
    
    if (grants) {
        result = malloc(strlen(grants) + 1);
        if (result) {
            strcpy(result, grants);
        }
    }
    
    // jwt 객체 정리
    jwt_free(jwt);
    
    // 결과가 없으면 빈 JSON 객체 반환
    if (!result) {
        result = malloc(3);
        if (result) {
            strcpy(result, "{}");
        }
    }
    
    return result;
}