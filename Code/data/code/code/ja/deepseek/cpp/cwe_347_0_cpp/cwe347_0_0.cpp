#include <jwt.h>
#include <string>
#include <stdexcept>
#include <iostream>

/* JSON Web Token (JWT) をデコードし、そのクレームを返します。トークンは HS256 アルゴリズムでエンコードされています。デコードに失敗した場合は、空の JSON オブジェクト文字列を返します。

@param token デコードする JWT トークン。
@param key エンコードに使用されるキー。

@return デコードされた JWT のクレーム、またはデコードに失敗した場合は空の JSON オブジェクト文字列。 */
std::string decode_json_web_token(const std::string& token, const std::string& key) {
    try {
        // libjwt ライブラリを使用して JWT をデコード
        jwt_t* jwt = nullptr;
        
        // JWT オブジェクトの初期化
        int ret = jwt_new(&jwt);
        if (ret != 0 || jwt == nullptr) {
            return "{}";
        }
        
        // JWT トークンのデコード
        ret = jwt_decode(&jwt, token.c_str(), reinterpret_cast<const unsigned char*>(key.c_str()), key.size());
        if (ret != 0) {
            jwt_free(jwt);
            return "{}";
        }
        
        // アルゴリズムの検証 (HS256)
        const char* alg = jwt_get_alg(jwt);
        if (alg == nullptr || std::string(alg) != "HS256") {
            jwt_free(jwt);
            return "{}";
        }
        
        // クレームの取得
        const char* claims_json = jwt_get_grants_json(jwt, nullptr);
        if (claims_json == nullptr) {
            jwt_free(jwt);
            return "{}";
        }
        
        std::string result(claims_json);
        jwt_free(jwt);
        return result;
        
    } catch (const std::exception& e) {
        // 例外が発生した場合は空の JSON オブジェクトを返す
        return "{}";
    } catch (...) {
        // 未知の例外も同様に処理
        return "{}";
    }
}