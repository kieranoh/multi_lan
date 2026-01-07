#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <jwt.h>

/* JSON Web Token (JWT) をデコードし、そのクレームを返します。トークンは HS256 アルゴリズムでエンコードされています。デコードに失敗した場合は、空の JSON オブジェクト文字列を返します。

@param token デコードする JWT トークン。
@param key エンコードに使用されるキー。

@return デコードされた JWT のクレーム、またはデコードに失敗した場合は空の JSON オブジェクト文字列。 */
char* decode_json_web_token(const char* token, const char* key) {
    jwt_t *jwt = NULL;
    char *json = NULL;

    // JWT をデコード
    if (jwt_decode(&jwt, token, key, 0) == 0) {
        // 成功した場合、JWT のクレームを JSON 形式で取得
        json = jwt_get_grants_json(jwt);
        jwt_free(jwt);
        return json;
    }

    // デコードに失敗した場合は空の JSON オブジェクト文字列を返す
    return "{}";
}