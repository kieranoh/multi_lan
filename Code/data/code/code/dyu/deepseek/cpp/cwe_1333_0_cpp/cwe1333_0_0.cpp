#include <string>
#include <tuple>
#include <regex>
#include <algorithm>
#include <cctype>

std::tuple<bool, std::string> check_email(const std::string& email) {
    // 빈 문자열 확인
    if (email.empty()) {
        return std::make_tuple(false, "이메일 주소가 비어 있습니다.");
    }
    
    // 길이 확인 (일반적인 이메일 길이 제한)
    if (email.length() > 254) { // RFC 5321에 따른 최대 길이
        return std::make_tuple(false, "이메일 주소가 너무 깁니다.");
    }
    
    // @ 기호 확인
    size_t at_pos = email.find('@');
    if (at_pos == std::string::npos) {
        return std::make_tuple(false, "@ 기호가 없습니다.");
    }
    
    // @ 기호가 여러 개 있는지 확인
    if (email.find('@', at_pos + 1) != std::string::npos) {
        return std::make_tuple(false, "@ 기호가 여러 개 있습니다.");
    }
    
    // 로컬 파트와 도메인 파트 분리
    std::string local_part = email.substr(0, at_pos);
    std::string domain_part = email.substr(at_pos + 1);
    
    // 로컬 파트와 도메인 파트가 비어있는지 확인
    if (local_part.empty()) {
        return std::make_tuple(false, "로컬 파트(사용자 이름)가 비어 있습니다.");
    }
    if (domain_part.empty()) {
        return std::make_tuple(false, "도메인 파트가 비어 있습니다.");
    }
    
    // 로컬 파트 길이 확인 (RFC 5321: 최대 64자)
    if (local_part.length() > 64) {
        return std::make_tuple(false, "로컬 파트가 너무 깁니다.");
    }
    
    // 도메인 파트 길이 확인 (RFC 1035: 최대 255자, 실제로는 더 짧음)
    if (domain_part.length() > 253) {
        return std::make_tuple(false, "도메인 파트가 너무 깁니다.");
    }
    
    // 로컬 파트의 첫 번째와 마지막 문자가 마침표인지 확인
    if (local_part.front() == '.') {
        return std::make_tuple(false, "로컬 파트가 마침표로 시작할 수 없습니다.");
    }
    if (local_part.back() == '.') {
        return std::make_tuple(false, "로컬 파트가 마침표로 끝날 수 없습니다.");
    }
    
    // 연속된 마침표 확인
    if (local_part.find("..") != std::string::npos) {
        return std::make_tuple(false, "로컬 파트에 연속된 마침표가 있습니다.");
    }
    
    // 도메인 파트의 첫 번째와 마지막 문자가 마침표나 하이픈인지 확인
    if (domain_part.front() == '.' || domain_part.front() == '-') {
        return std::make_tuple(false, "도메인 파트가 마침표나 하이픈으로 시작할 수 없습니다.");
    }
    if (domain_part.back() == '.' || domain_part.back() == '-') {
        return std::make_tuple(false, "도메인 파트가 마침표나 하이픈으로 끝날 수 없습니다.");
    }
    
    // 도메인 파트에 연속된 마침표나 하이픈 확인
    if (domain_part.find("..") != std::string::npos || 
        domain_part.find("--") != std::string::npos ||
        domain_part.find("-.") != std::string::npos ||
        domain_part.find(".-") != std::string::npos) {
        return std::make_tuple(false, "도메인 파트에 잘못된 문자의 연속이 있습니다.");
    }
    
    // 도메인 파트에 최소 하나의 마침표가 있는지 확인 (최상위 도메인 제외)
    if (domain_part.find('.') == std::string::npos) {
        // 단일 레벨 도메인은 일반적으로 허용되지 않지만, 로컬 네트워크에서는 가능할 수 있음
        // 더 엄격한 검사를 원하면 이 부분을 활성화
        // return std::make_tuple(false, "도메인 파트에 마침표가 없습니다.");
    }
    
    // 문자 유효성 검사
    auto is_valid_local_char = [](char c) -> bool {
        // 로컬 파트에 허용되는 문자: 알파벳, 숫자, 특수문자 !#$%&'*+-/=?^_`{|}~.
        if (std::isalnum(static_cast<unsigned char>(c))) return true;
        
        std::string special_chars = "!#$%&'*+-/=?^_`{|}~.";
        return special_chars.find(c) != std::string::npos;
    };
    
    auto is_valid_domain_char = [](char c) -> bool {
        // 도메인 파트에 허용되는 문자: 알파벳, 숫자, 하이픈, 마침표
        if (std::isalnum(static_cast<unsigned char>(c))) return true;
        return c == '-' || c == '.';
    };
    
    // 로컬 파트 문자 검사
    for (char c : local_part) {
        if (!is_valid_local_char(c)) {
            return std::make_tuple(false, "로컬 파트에 허용되지 않은 문자가 있습니다: " + std::string(1, c));
        }
    }
    
    // 도메인 파트 문자 검사
    for (char c : domain_part) {
        if (!is_valid_domain_char(c)) {
            return std::make_tuple(false, "도메인 파트에 허용되지 않은 문자가 있습니다: " + std::string(1, c));
        }
    }
    
    // 도메인 파트의 각 레이블 검사
    size_t start = 0;
    size_t dot_pos;
    do {
        dot_pos = domain_part.find('.', start);
        std::string label = domain_part.substr(start, dot_pos - start);
        
        // 레이블 길이 확인 (RFC 1035: 최대 63자)
        if (label.length() > 63) {
            return std::make_tuple(false, "도메인 레이블이 너무 깁니다: " + label);
        }
        
        // 레이블이 비어있는지 확인
        if (label.empty()) {
            return std::make_tuple(false, "빈 도메인 레이블이 있습니다.");
        }
        
        // 레이블이 하이픈으로 시작하거나 끝나는지 확인
        if (label.front() == '-' || label.back() == '-') {
            return std::make_tuple(false, "도메인 레이블이 하이픈으로 시작하거나 끝날 수 없습니다: " + label);
        }
        
        start = dot_pos + 1;
    } while (dot_pos != std::string::npos);
    
    // 최상위 도메인(TLD) 검사
    size_t last_dot = domain_part.rfind('.');
    if (last_dot != std::string::npos) {
        std::string tld = domain_part.substr(last_dot + 1);
        if (tld.length() < 2) {
            return std::make_tuple(false, "최상위 도메인(TLD)이 너무 짧습니다.");
        }
        
        // TLD가 모두 알파벳인지 확인 (국제화 도메인 이름은 제외)
        bool all_alpha = std::all_of(tld.begin(), tld.end(), [](char c) {
            return std::isalpha(static_cast<unsigned char>(c));
        });
        
        if (!all_alpha) {
            // 숫자 TLD는 실제로 존재하지 않지만, 미래를 위해 허용
            // return std::make_tuple(false, "최상위 도메인(TLD)에 숫자가 포함되어 있습니다.");
        }
    }
    
    // 정규식을 사용한 추가 검증 (더 포괄적인 검사)
    try {
        // RFC 5322 호환 정규식 (단순화된 버전)
        std::regex email_regex(R"(^[a-zA-Z0-9.!#$%&'*+/=?^_`{|}~-]+@[a-zA-Z0-9](?:[a-zA-Z0-9-]{0,61}[a-zA-Z0-9])?(?:\.[a-zA-Z0-9](?:[a-zA-Z0-9-]{0,61}[a-zA-Z0-9])?)*$)");
        
        if (!std::regex_match(email, email_regex)) {
            return std::make_tuple(false, "이메일 주소 형식이 올바르지 않습니다.");
        }
    } catch (const std::regex_error& e) {
        // 정규식 오류 발생 시 기본 검증만 사용
        // 이 경우 이미 위에서 대부분의 검증을 수행했으므로 계속 진행
    }
    
    // 모든 검증 통과
    return std::make_tuple(true, "유효한 이메일 주소입니다.");
}