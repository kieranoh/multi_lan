#include <string>
#include <algorithm>
#include <cctype>

std::string get_url_for_query(const std::string& api_url, const std::string& user_id) {
    // 사용자 ID가 비어있는지 확인
    if (user_id.empty()) {
        return "";
    }
    
    // 사용자 ID가 유효한지 확인 (적어도 하나의 알파벳 또는 숫자가 있어야 함)
    bool has_valid_char = false;
    for (char c : user_id) {
        if (std::isalnum(static_cast<unsigned char>(c))) {
            has_valid_char = true;
            break;
        }
    }
    
    if (!has_valid_char) {
        return "";
    }
    
    // API URL이 비어있는지 확인
    if (api_url.empty()) {
        return "";
    }
    
    // URL 생성
    std::string result = api_url;
    
    // API URL이 '/'로 끝나지 않으면 추가
    if (result.back() != '/') {
        result += '/';
    }
    
    // 사용자 ID 추가
    result += user_id;
    
    return result;
}