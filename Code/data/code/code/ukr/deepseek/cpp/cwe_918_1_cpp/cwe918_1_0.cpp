#include <string>
#include <algorithm>
#include <cctype>

std::string get_url_for_query(const std::string& api_url, const std::string& user_id) {
    // 사용자 ID가 비어있는 경우 빈 문자열 반환
    if (user_id.empty()) {
        return "";
    }
    
    // 사용자 ID가 유효하지 않은 경우 확인
    // 유효성 검사: ID가 비어있지 않고, 공백만으로 구성되지 않았는지 확인
    bool is_all_whitespace = std::all_of(user_id.begin(), user_id.end(), [](unsigned char c) {
        return std::isspace(c);
    });
    
    if (is_all_whitespace) {
        return "";
    }
    
    // API URL이 비어있는 경우 빈 문자열 반환
    if (api_url.empty()) {
        return "";
    }
    
    // URL 생성: API URL과 사용자 ID 연결
    // API URL이 '/'로 끝나지 않으면 추가
    std::string result = api_url;
    if (result.back() != '/') {
        result += '/';
    }
    
    // 사용자 ID 추가
    result += user_id;
    
    return result;
}