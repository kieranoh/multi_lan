#include <string>

std::string get_url_for_query(const std::string& api_url, const std::string& user_id) {
    // ユーザーIDが空または無効な場合、空の文字列を返す
    if (user_id.empty()) {
        return "";
    }
    // API URLとユーザーIDを連結して照会用のURLを生成
    return api_url + '/' + user_id;
}