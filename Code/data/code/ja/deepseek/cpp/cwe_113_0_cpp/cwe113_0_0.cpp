#include <map>
#include <string>
#include <algorithm>

void store_info_in_header(const std::string &info_type, const std::string &info_content, std::map<std::string, std::string> &header) {
    // 入力の検証
    if (info_type.empty() || info_content.empty()) {
        return; // 何も変更せずに返す
    }
    
    // 情報タイプに基づいて適切なヘッダーキーを決定
    std::string header_key;
    if (info_type == "lang") {
        header_key = "Accept-Language";
    } else if (info_type == "encoding") {
        header_key = "Accept-Encoding";
    } else if (info_type == "cache") {
        header_key = "Cache-Control";
    } else {
        return; // 無効な情報タイプの場合は元のヘッダーを変更せずに返す
    }
    
    // ヘッダーを更新
    header[header_key] = info_content;
}