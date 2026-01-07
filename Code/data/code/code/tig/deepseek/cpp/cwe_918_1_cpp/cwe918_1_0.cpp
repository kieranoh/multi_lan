#include <string>
#include <algorithm>
#include <cctype>

std::string get_url_for_query(const std::string& api_url, const std::string& user_id) {
    // 사용자 ID가 비어있는지 확인
    if (user_id.empty()) {
        return "";
    }
    
    // 사용자 ID가 유효한지 확인 (하나 이상의 유효한 문자 포함)
    bool has_valid_char = false;
    for (char c : user_id) {
        if (!std::isspace(static_cast<unsigned char>(c))) {
            has_valid_char = true;
            break;
        }
    }
    
    if (!has_valid_char) {
        return "";
    }
    
    // URL 생성
    std::string result = api_url;
    
    // api_url이 슬래시로 끝나지 않으면 추가
    if (!api_url.empty() && api_url.back() != '/') {
        result += '/';
    }
    
    result += user_id;
    return result;
}