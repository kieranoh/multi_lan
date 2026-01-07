#include <string>
#include <algorithm>
#include <cctype>

std::string get_url_for_query(const std::string& api_url, const std::string& user_id) {
    // 사용자 ID가 비어 있는지 확인
    if (user_id.empty()) {
        return "";
    }
    
    // 사용자 ID가 유효한지 확인 (공백만 있는 경우 등)
    bool is_valid = false;
    for (char c : user_id) {
        if (!std::isspace(static_cast<unsigned char>(c))) {
            is_valid = true;
            break;
        }
    }
    
    if (!is_valid) {
        return "";
    }
    
    // URL 생성
    std::string result = api_url;
    
    // api_url이 '/'로 끝나지 않으면 추가
    if (!result.empty() && result.back() != '/') {
        result += '/';
    }
    
    // 사용자 ID 추가
    result += user_id;
    
    return result;
}