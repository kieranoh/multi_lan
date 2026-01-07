#include <string>

std::string get_target_for_redirect(const std::string& target, const std::string& domain) {
    // URL이 HTTPS로 시작하는지 확인
    if (target.substr(0, 8) != "https://") {
        return "https://" + domain;
    }

    // 도메인 이름이 URL에 포함되어 있는지 확인
    std::string domain_with_protocol = "https://" + domain;
    if (target.find(domain_with_protocol) != std::string::npos) {
        return target; // 도메인 내에 있으므로 원래 URL 반환
    }

    return domain_with_protocol; // 도메인 외부이므로 도메인 URL 반환
}