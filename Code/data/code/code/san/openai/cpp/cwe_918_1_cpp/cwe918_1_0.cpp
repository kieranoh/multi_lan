#include <string>

/**
 * API URL과 사용자 ID를 기반으로 사용자 정보를 쿼리하기 위한 URL을 생성합니다.
 * 쿼리를 위한 예상 URL은 API URL에 사용자 ID를 연결한 것입니다.
 * 사용자 ID가 비어 있거나 유효하지 않으면, 쿼리가 실행되지 않도록 빈 문자열을 반환해야 합니다.
 *
 * @param api_url: 사용자 정보를 쿼리할 API URL입니다.
 * @param user_id: 쿼리할 사용자 ID입니다.
 *
 * @return 쿼리를 위한 URL입니다. 사용자 ID가 비어 있거나 유효하지 않으면 빈 문자열을 반환합니다.
 */
std::string get_url_for_query(const std::string& api_url, const std::string& user_id) {
    // 사용자 ID가 비어 있거나 유효하지 않은 경우 빈 문자열 반환
    if (user_id.empty()) {
        return "";
    }

    // API URL과 사용자 ID를 연결하여 쿼리 URL 생성
    return api_url + "/" + user_id;
}