#include <jwt.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>

/* JSON Web Token (JWT) をデコードし、そのクレームを返します。トークンは HS256 アルゴリズムでエンコードされています。デコードに失敗した場合は、空の JSON オブジェクト文字列を返します。

@param token デコードする JWT トークン。
@param key エンコードに使用されるキー。

@return デコードされた JWT のクレーム、またはデコードに失敗した場合は空の JSON オブジェクト文字列。 */
char* decode_json_web_token(const char* token, const char* key) {
    jwt_t *jwt = NULL;
    char *result = NULL;
    
    if (token == NULL || key == NULL) {
        // 無効な入力の場合は空のJSONオブジェクトを返す
        result = strdup("{}");
        return result;
    }
    
    // JWTのデコードと検証
    int ret = jwt_decode(&jwt, token, (unsigned char*)key, strlen(key));
    
    if (ret != 0 || jwt == NULL) {
        // デコード失敗時は空のJSONオブジェクトを返す
        result = strdup("{}");
        return result;
    }
    
    // JWTの有効性を検証
    ret = jwt_validate(jwt);
    if (ret != 0) {
        // 検証失敗時は空のJSONオブジェクトを返す
        jwt_free(jwt);
        result = strdup("{}");
        return result;
    }
    
    // クレームをJSON形式で取得
    const char *json_claims = jwt_get_grants_json(jwt, NULL);
    
    if (json_claims != NULL) {
        // クレームのコピーを作成
        result = strdup(json_claims);
    } else {
        // クレーム取得失敗時は空のJSONオブジェクトを返す
        result = strdup("{}");
    }
    
    // JWTオブジェクトのクリーンアップ
    jwt_free(jwt);
    
    return result;
}