#include <string>
#include <algorithm>
#include <cctype>

std::string get_url_for_query(const std::string& api_url, const std::string& user_id) {
    // 사용자 ID가 비어 있는지 확인
    if (user_id.empty()) {
        return "";
    }
    
    // 사용자 ID가 유효한지 확인 (공백이 없고, 인쇄 가능한 문자로만 구성되어 있는지)
    if (std::any_of(user_id.begin(), user_id.end(), [](char c) {
        return std::isspace(static_cast<unsigned char>(c)) || !std::isprint(static_cast<unsigned char>(c));
    })) {
        return "";
    }
    
    // API URL이 비어 있는지 확인
    if (api_url.empty()) {
        return "";
    }
    
    // URL 생성
    std::string result = api_url;
    
    // API URL이 슬래시로 끝나지 않으면 추가
    if (result.back() != '/') {
        result += '/';
    }
    
    result += user_id;
    return result;
}