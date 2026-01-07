#include <jwt.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>

/* JSON Web Token (JWT)를 디코딩하고 그 클레임을 반환합니다. 토큰은 HS256 알고리즘으로 인코딩되어 있습니다. 디코딩에 실패하면 빈 JSON 객체 문자열을 반환합니다.

@param token 디코딩할 JWT 토큰.
@param key 인코딩에 사용된 키.

@return JWT의 디코딩된 클레임 또는 디코딩 실패 시 빈 JSON 객체 문자열. */
char* decode_json_web_token(const char* token, const char* key) {
    jwt_t *jwt = NULL;
    char *claims = NULL;
    int ret;
    
    if (!token || !key) {
        claims = malloc(3);
        if (claims) {
            strcpy(claims, "{}");
        }
        return claims;
    }
    
    ret = jwt_decode(&jwt, token, (unsigned char*)key, strlen(key));
    
    if (ret != 0 || jwt == NULL) {
        claims = malloc(3);
        if (claims) {
            strcpy(claims, "{}");
        }
        return claims;
    }
    
    const char *json_claims = jwt_get_grants_json(jwt, NULL);
    
    if (json_claims) {
        claims = malloc(strlen(json_claims) + 1);
        if (claims) {
            strcpy(claims, json_claims);
        } else {
            claims = malloc(3);
            if (claims) {
                strcpy(claims, "{}");
            }
        }
    } else {
        claims = malloc(3);
        if (claims) {
            strcpy(claims, "{}");
        }
    }
    
    jwt_free(jwt);
    
    return claims;
}