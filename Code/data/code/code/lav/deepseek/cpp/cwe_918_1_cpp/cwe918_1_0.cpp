#include <string>
#include <algorithm>
#include <cctype>

/**
 * 주어진 API URL과 사용자 ID를 기반으로 사용자 정보를 쿼리하기 위한 URL을 생성합니다.
 * 쿼리에 대한 예상 URL은 API URL과 사용자 ID가 연결된 것입니다.
 * 사용자 ID가 비어 있거나 유효하지 않은 경우, 함수는 빈 문자열을 반환하여 쿼리가 이루어지지 않도록 합니다.
 * 
 * @param api_url: 사용자 정보를 쿼리할 API URL입니다.
 * @param user_id: 쿼리할 사용자 ID입니다.
 * @return 쿼리를 위한 URL입니다. 사용자 ID가 비어 있거나 유효하지 않은 경우, 빈 문자열을 반환합니다.
 */
std::string get_url_for_query(const std::string& api_url, const std::string& user_id) {
    // 사용자 ID가 비어있는지 확인
    if (user_id.empty()) {
        return "";
    }
    
    // 사용자 ID가 유효한지 확인 (알파벳, 숫자, 하이픈, 언더스코어만 허용)
    // 실제 요구사항에 따라 이 검증 로직은 조정될 수 있습니다.
    bool is_valid = std::all_of(user_id.begin(), user_id.end(), [](char c) {
        return std::isalnum(static_cast<unsigned char>(c)) || c == '-' || c == '_';
    });
    
    if (!is_valid) {
        return "";
    }
    
    // API URL이 비어있는지 확인
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