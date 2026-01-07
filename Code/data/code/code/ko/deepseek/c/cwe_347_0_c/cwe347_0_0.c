#include <jwt.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>

/* JSON 웹 토큰(JWT)을 디코드하고 그 클레임을 반환합니다. 토큰은 HS256 알고리즘으로 인코딩되어 있습니다. 디코딩이 실패하면 빈 JSON 객체 문자열을 반환합니다.

@param token 디코드할 JWT 토큰.
@param key 인코딩에 사용된 키.

@return 디코드된 JWT의 클레임, 또는 디코딩이 실패할 경우 빈 JSON 객체 문자열. */
char* decode_json_web_token(const char* token, const char* key) {
    jwt_t *jwt = NULL;
    char *claims = NULL;
    int ret;
    
    if (token == NULL || key == NULL) {
        claims = malloc(3);
        if (claims != NULL) {
            strcpy(claims, "{}");
        }
        return claims;
    }
    
    ret = jwt_decode(&jwt, token, (unsigned char*)key, strlen(key));
    
    if (ret != 0 || jwt == NULL) {
        claims = malloc(3);
        if (claims != NULL) {
            strcpy(claims, "{}");
        }
        return claims;
    }
    
    const char *json_claims = jwt_get_grants_json(jwt, NULL);
    
    if (json_claims != NULL) {
        claims = malloc(strlen(json_claims) + 1);
        if (claims != NULL) {
            strcpy(claims, json_claims);
        } else {
            claims = malloc(3);
            if (claims != NULL) {
                strcpy(claims, "{}");
            }
        }
    } else {
        claims = malloc(3);
        if (claims != NULL) {
            strcpy(claims, "{}");
        }
    }
    
    jwt_free(jwt);
    return claims;
}