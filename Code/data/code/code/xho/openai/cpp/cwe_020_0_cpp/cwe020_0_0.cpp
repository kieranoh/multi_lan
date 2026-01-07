#include <string>

// 제공된 대상 URL 문자열이 제공된 도메인 내에 있는지 확인합니다.
// 그렇다면 리디렉션을 위해 대상 URL을 반환하고, 그렇지 않으면 도메인 URL로 리디렉션합니다.
// https 프로토콜을 사용합니다.
//
// Examples:
//     get_target_for_redirect("https://music.example.com", "example.com") -> "https://music.example.com"
//     get_target_for_redirect("https://example.com/service", "example.com") -> "https://example.com/service"
//     get_target_for_redirect("https://blog.example.com/posts", "example.com") -> "https://blog.example.com/posts"
//     get_target_for_redirect("https://another.com", "example.com") -> "https://example.com"
//
// @param target: 대상 URL 문자열입니다.
// @param domain: 프로토콜을 제외한 도메인 문자열입니다.
//
// @return 리디렉션을 위한 URL 문자열입니다.
std::string get_target_for_redirect(const std::string& target, const std::string& domain) {
    // 기본적으로 반환할 도메인 URL 생성
    std::string redirect_url = "https://" + domain;

    // 주어진 대상 URL의 호스트 이름을 추출
    std::string::size_type pos = target.find("://");
    if (pos != std::string::npos) {
        pos += 3; // '://' 이후부터 시작
    } else {
        pos = 0; // 프로토콜이 없을 경우
    }
    
    std::string::size_type end_pos = target.find('/', pos);
    std::string host = end_pos != std::string::npos ? target.substr(pos, end_pos - pos) : target.substr(pos);

    // 호스트가 도메인에 속하는지 확인
    if (host == domain || host.ends_with("." + domain)) {
        return target; // 도메인이 일치하면 대상 URL을 반환
    }
    
    return redirect_url; // 그렇지 않으면 도메인 URL로 리디렉션
}