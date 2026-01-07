#include <tuple>
#include <string>
#include <regex>
#include <algorithm>
#include <cctype>

std::tuple<bool, std::string> check_email(const std::string& email) {
    // 빈 문자열 확인
    if (email.empty()) {
        return std::make_tuple(false, "이메일 주소가 비어 있습니다.");
    }
    
    // 최소 길이 확인 (예: a@b.c = 5자)
    if (email.length() < 5) {
        return std::make_tuple(false, "이메일 주소가 너무 짧습니다.");
    }
    
    // 최대 길이 확인 (RFC 5321: 254자)
    if (email.length() > 254) {
        return std::make_tuple(false, "이메일 주소가 너무 깁니다 (254자 초과).");
    }
    
    // @ 기호 확인
    size_t at_pos = email.find('@');
    if (at_pos == std::string::npos) {
        return std::make_tuple(false, "@ 기호가 없습니다.");
    }
    
    // @ 기호가 여러 개인지 확인
    if (email.find('@', at_pos + 1) != std::string::npos) {
        return std::make_tuple(false, "@ 기호가 여러 개 있습니다.");
    }
    
    // 로컬 파트와 도메인 파트 분리
    std::string local_part = email.substr(0, at_pos);
    std::string domain_part = email.substr(at_pos + 1);
    
    // 로컬 파트가 비어있는지 확인
    if (local_part.empty()) {
        return std::make_tuple(false, "로컬 파트(사용자명)가 비어 있습니다.");
    }
    
    // 도메인 파트가 비어있는지 확인
    if (domain_part.empty()) {
        return std::make_tuple(false, "도메인 파트가 비어 있습니다.");
    }
    
    // 로컬 파트 길이 확인 (RFC 5321: 64자)
    if (local_part.length() > 64) {
        return std::make_tuple(false, "로컬 파트가 너무 깁니다 (64자 초과).");
    }
    
    // 로컬 파트 시작과 끝이 점(.)인지 확인
    if (local_part.front() == '.') {
        return std::make_tuple(false, "로컬 파트가 점(.)으로 시작할 수 없습니다.");
    }
    if (local_part.back() == '.') {
        return std::make_tuple(false, "로컬 파트가 점(.)으로 끝날 수 없습니다.");
    }
    
    // 로컬 파트에 연속된 점 확인
    if (local_part.find("..") != std::string::npos) {
        return std::make_tuple(false, "로컬 파트에 연속된 점(..)이 있습니다.");
    }
    
    // 도메인 파트 시작과 끝이 점(.)인지 확인
    if (domain_part.front() == '.') {
        return std::make_tuple(false, "도메인 파트가 점(.)으로 시작할 수 없습니다.");
    }
    if (domain_part.back() == '.') {
        return std::make_tuple(false, "도메인 파트가 점(.)으로 끝날 수 없습니다.");
    }
    
    // 도메인 파트에 연속된 점 확인
    if (domain_part.find("..") != std::string::npos) {
        return std::make_tuple(false, "도메인 파트에 연속된 점(..)이 있습니다.");
    }
    
    // 도메인 파트에 최소 하나의 점이 있는지 확인
    if (domain_part.find('.') == std::string::npos) {
        return std::make_tuple(false, "도메인 파트에 점(.)이 없습니다.");
    }
    
    // 도메인 레이블 길이 확인 (RFC 1035: 63자)
    size_t start = 0;
    size_t dot_pos;
    while ((dot_pos = domain_part.find('.', start)) != std::string::npos) {
        std::string label = domain_part.substr(start, dot_pos - start);
        if (label.empty()) {
            return std::make_tuple(false, "도메인 레이블이 비어 있습니다.");
        }
        if (label.length() > 63) {
            return std::make_tuple(false, "도메인 레이블이 너무 깁니다 (63자 초과).");
        }
        start = dot_pos + 1;
    }
    
    // 마지막 레이블 확인
    std::string last_label = domain_part.substr(start);
    if (last_label.empty()) {
        return std::make_tuple(false, "마지막 도메인 레이블이 비어 있습니다.");
    }
    if (last_label.length() > 63) {
        return std::make_tuple(false, "마지막 도메인 레이블이 너무 깁니다 (63자 초과).");
    }
    
    // TLD(최상위 도메인)가 최소 2자 이상인지 확인 (일반적인 경우)
    if (last_label.length() < 2) {
        return std::make_tuple(false, "최상위 도메인이 너무 짧습니다.");
    }
    
    // 문자 유효성 검사를 위한 정규식
    // RFC 5322를 완전히 준수하는 정규식은 매우 복잡하므로, 일반적인 경우를 다루는 간소화된 버전 사용
    std::regex email_regex(
        R"(^[a-zA-Z0-9.!#$%&'*+/=?^_`{|}~-]+@[a-zA-Z0-9](?:[a-zA-Z0-9-]{0,61}[a-zA-Z0-9])?(?:\.[a-zA-Z0-9](?:[a-zA-Z0-9-]{0,61}[a-zA-Z0-9])?)*$)"
    );
    
    if (!std::regex_match(email, email_regex)) {
        return std::make_tuple(false, "이메일 주소 형식이 유효하지 않습니다.");
    }
    
    // 추가적인 도메인 검증: 도메인 레이블이 하이픈으로 시작하거나 끝나지 않는지 확인
    start = 0;
    while ((dot_pos = domain_part.find('.', start)) != std::string::npos) {
        std::string label = domain_part.substr(start, dot_pos - start);
        if (label.front() == '-' || label.back() == '-') {
            return std::make_tuple(false, "도메인 레이블이 하이픈으로 시작하거나 끝날 수 없습니다.");
        }
        start = dot_pos + 1;
    }
    
    // 마지막 레이블 확인
    if (last_label.front() == '-' || last_label.back() == '-') {
        return std::make_tuple(false, "최상위 도메인이 하이픈으로 시작하거나 끝날 수 없습니다.");
    }
    
    // 모든 검사를 통과한 경우
    return std::make_tuple(true, "유효한 이메일 주소입니다.");
}