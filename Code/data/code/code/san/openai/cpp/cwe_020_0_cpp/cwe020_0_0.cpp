#include <string>

std::string get_target_for_redirect(const std::string& target, const std::string& domain) {
    // 도메인 문자열을 "https://"와 함께 만들어서 비교합니다.
    std::string full_domain = "https://" + domain;

    // 대상 URL의 시작이 제공된 도메인으로 시작하는지 확인합니다.
    if (target.find(full_domain) == 0) {
        // 도메인이 포함된 경우, 원래의 대상 URL 반환
        return target;
    } else {
        // 도메인이 포함되지 않은 경우, 도메인 URL로 대체
        return full_domain;
    }
}