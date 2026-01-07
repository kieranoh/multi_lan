#include <string>
#include <algorithm>
#include <cctype>

std::string get_url_for_query(const std::string& api_url, const std::string& user_id) {
    // ユーザーIDが空の場合は空文字列を返す
    if (user_id.empty()) {
        return "";
    }
    
    // ユーザーIDが無効かどうかをチェック（空白文字のみの場合も無効とみなす）
    bool is_invalid = std::all_of(user_id.begin(), user_id.end(), [](char c) {
        return std::isspace(static_cast<unsigned char>(c));
    });
    
    if (is_invalid) {
        return "";
    }
    
    // API URLの末尾にスラッシュがない場合は追加
    std::string result = api_url;
    if (!result.empty() && result.back() != '/') {
        result += '/';
    }
    
    // ユーザーIDを追加
    result += user_id;
    
    return result;
}