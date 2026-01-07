#include <string>
#include <algorithm>
#include <cctype>

std::string get_url_for_query(const std::string& api_url, const std::string& user_id) {
    // 사용자 ID가 비어있는지 확인
    if (user_id.empty()) {
        return "";
    }
    
    // 사용자 ID가 유효한지 확인 (공백만 있는 경우도 유효하지 않음)
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
    
    // API URL이 비어있는 경우 빈 문자열 반환
    if (api_url.empty()) {
        return "";
    }
    
    // API URL이 '/'로 끝나는지 확인하고 적절히 조합
    std::string result = api_url;
    if (result.back() != '/') {
        result += '/';
    }
    result += user_id;
    
    return result;
}