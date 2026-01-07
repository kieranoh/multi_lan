#include <tuple>
#include <string>
#include <regex>
#include <algorithm>
#include <cctype>

std::tuple<bool, std::string> check_email(const std::string& email) {
    // 빈 문자열 체크
    if (email.empty()) {
        return std::make_tuple(false, "이메일 주소가 비어 있습니다.");
    }
    
    // 길이 체크 (일반적인 이메일 길이 제한)
    if (email.length() > 254) { // RFC 5321에 따른 최대 길이
        return std::make_tuple(false, "이메일 주소가 너무 깁니다.");
    }
    
    // @ 기호 개수 체크
    int at_count = std::count(email.begin(), email.end(), '@');
    if (at_count != 1) {
        return std::make_tuple(false, "정확히 하나의 @ 기호가 필요합니다.");
    }
    
    // @ 기호 위치 체크
    size_t at_pos = email.find('@');
    if (at_pos == 0 || at_pos == email.length() - 1) {
        return std::make_tuple(false, "@ 기호는 로컬 파트와 도메인 파트 사이에 위치해야 합니다.");
    }
    
    // 로컬 파트와 도메인 파트 분리
    std::string local_part = email.substr(0, at_pos);
    std::string domain_part = email.substr(at_pos + 1);
    
    // 로컬 파트 길이 체크 (RFC 5321: 최대 64자)
    if (local_part.length() > 64) {
        return std::make_tuple(false, "로컬 파트가 너무 깁니다 (최대 64자).");
    }
    
    // 도메인 파트 길이 체크
    if (domain_part.length() > 253) {
        return std::make_tuple(false, "도메인 파트가 너무 깁니다.");
    }
    
    // 로컬 파트가 비어있는지 체크
    if (local_part.empty()) {
        return std::make_tuple(false, "로컬 파트가 비어 있습니다.");
    }
    
    // 도메인 파트가 비어있는지 체크
    if (domain_part.empty()) {
        return std::make_tuple(false, "도메인 파트가 비어 있습니다.");
    }
    
    // 로컬 파트의 첫 문자와 마지막 문자 체크
    if (local_part.front() == '.' || local_part.back() == '.') {
        return std::make_tuple(false, "로컬 파트는 마침표로 시작하거나 끝날 수 없습니다.");
    }
    
    // 연속된 마침표 체크
    if (local_part.find("..") != std::string::npos) {
        return std::make_tuple(false, "로컬 파트에 연속된 마침표가 있습니다.");
    }
    
    // 도메인 파트의 첫 문자와 마지막 문자 체크
    if (domain_part.front() == '.' || domain_part.back() == '.') {
        return std::make_tuple(false, "도메인 파트는 마침표로 시작하거나 끝날 수 없습니다.");
    }
    
    // 도메인 파트에 연속된 마침표 체크
    if (domain_part.find("..") != std::string::npos) {
        return std::make_tuple(false, "도메인 파트에 연속된 마침표가 있습니다.");
    }
    
    // 도메인 파트에 최소 하나의 마침표가 있는지 확인 (최상위 도메인 제외)
    if (std::count(domain_part.begin(), domain_part.end(), '.') == 0) {
        // 단일 레벨 도메인은 일반적으로 허용되지 않지만, 로컬 네트워크에서는 가능할 수 있음
        // 여기서는 허용하되 경고를 추가
        // 실제 구현에서는 조직의 정책에 따라 다를 수 있음
    }
    
    // 도메인 레이블 길이 체크 (각 레이블은 1-63자)
    size_t start = 0;
    size_t dot_pos;
    while ((dot_pos = domain_part.find('.', start)) != std::string::npos) {
        std::string label = domain_part.substr(start, dot_pos - start);
        if (label.empty() || label.length() > 63) {
            return std::make_tuple(false, "도메인 레이블이 비어있거나 너무 깁니다 (최대 63자).");
        }
        start = dot_pos + 1;
    }
    
    // 마지막 레이블 체크
    std::string last_label = domain_part.substr(start);
    if (last_label.empty() || last_label.length() > 63) {
        return std::make_tuple(false, "도메인 레이블이 비어있거나 너무 깁니다 (최대 63자).");
    }
    
    // 문자 유효성 검사를 위한 정규식
    // 이 정규식은 일반적인 이메일 형식을 검사하지만, RFC 5322의 모든 경우를 다루지는 않음
    // false negative를 피하기 위해 비교적 관대한 패턴 사용
    std::regex email_pattern(
        R"(^[a-zA-Z0-9.!#$%&'*+/=?^_`{|}~-]+@[a-zA-Z0-9](?:[a-zA-Z0-9-]{0,61}[a-zA-Z0-9])?(?:\.[a-zA-Z0-9](?:[a-zA-Z0-9-]{0,61}[a-zA-Z0-9])?)*$)"
    );
    
    if (!std::regex_match(email, email_pattern)) {
        // 더 세부적인 검사를 위해 각 파트별로 검사
        bool local_valid = true;
        bool domain_valid = true;
        
        // 로컬 파트 문자 검사
        for (char c : local_part) {
            if (!std::isalnum(static_cast<unsigned char>(c)) && 
                c != '.' && c != '!' && c != '#' && c != '$' && c != '%' && 
                c != '&' && c != '\'' && c != '*' && c != '+' && c != '-' && 
                c != '/' && c != '=' && c != '?' && c != '^' && c != '_' && 
                c != '`' && c != '{' && c != '|' && c != '}' && c != '~') {
                local_valid = false;
                break;
            }
        }
        
        // 도메인 파트 문자 검사
        for (char c : domain_part) {
            if (!std::isalnum(static_cast<unsigned char>(c)) && c != '.' && c != '-') {
                domain_valid = false;
                break;
            }
        }
        
        if (!local_valid || !domain_valid) {
            return std::make_tuple(false, "이메일 주소에 허용되지 않는 문자가 포함되어 있습니다.");
        }
    }
    
    // 도메인 파트의 마지막 레이블(최상위 도메인) 체크
    // 최소 2자 이상이어야 하지만, 일부 국가 코드는 1자일 수 있음 (예: x.com)
    // 여기서는 1자 이상으로 허용
    if (last_label.length() < 1) {
        return std::make_tuple(false, "최상위 도메인이 너무 짧습니다.");
    }
    
    // 모든 검사를 통과한 경우
    return std::make_tuple(true, "유효한 이메일 주소입니다.");
}