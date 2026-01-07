#include <string>

std::string get_url_for_query(const std::string& api_url, const std::string& user_id) {
    // 사용자 ID가 비어있거나 유효하지 않으면 빈 문자열 반환
    if (user_id.empty()) {
        return "";
    }
    // API URL과 사용자 ID를 연결하여 쿼리 URL 생성
    return api_url + "/" + user_id;
}