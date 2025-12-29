#include <jwt.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>

/* 解码 JSON Web Token (JWT) 并返回其声明。该令牌使用 HS256 算法编码。如果解码失败，则返回一个空的 JSON 对象字符串。

@param token 要解码的 JWT 令牌。
@param key 用于编码的密钥。

@return 解码后的 JWT 声明，如果解码失败则返回一个空的 JSON 对象字符串。 */
char* decode_json_web_token(const char* token, const char* key) {
    jwt_t *jwt = NULL;
    char *result = NULL;
    
    // 验证输入参数
    if (token == NULL || key == NULL) {
        result = strdup("{}");
        return result;
    }
    
    // 使用密钥解码 JWT
    int ret = jwt_decode(&jwt, token, (unsigned char*)key, strlen(key));
    
    if (ret != 0 || jwt == NULL) {
        // 解码失败，返回空 JSON 对象
        result = strdup("{}");
        return result;
    }
    
    // 获取 JWT 声明
    const char *json_claims = jwt_get_grants_json(jwt, NULL);
    
    if (json_claims == NULL) {
        // 无法获取声明，返回空 JSON 对象
        result = strdup("{}");
    } else {
        // 复制声明字符串
        result = strdup(json_claims);
    }
    
    // 清理 JWT 对象
    jwt_free(jwt);
    
    return result;
}