#include <jwt.h>
#include <string>
#include <nlohmann/json.hpp>

std::string decode_json_web_token(const std::string& token, const std::string& key) {
    jwt_t *jwt = nullptr;
    int ret = jwt_decode(&jwt, token.c_str(), (unsigned char*)key.c_str(), key.length());

    if (ret != 0) {
        // デコードに失敗した場合、空の JSON オブジェクト文字列を返す
        return "{}";
    }

    // JWT のペイロードを取得
    const char *payload = jwt_get_payload(jwt);
    std::string json_str = std::string(payload);

    // jwt_t 構造体のメモリを解放
    jwt_free(jwt);

    return json_str;
}