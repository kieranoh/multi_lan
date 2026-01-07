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
    
    // 길이 체크 (일반적으로 254자 제한, 로컬 파트 64자 제한)
    if (email.length() > 254) {
        return std::make_tuple(false, "이메일 주소가 너무 깁니다 (254자 초과).");
    }
    
    // @ 기호 체크
    size_t at_pos = email.find('@');
    if (at_pos == std::string::npos) {
        return std::make_tuple(false, "@ 기호가 없습니다.");
    }
    
    // @ 기호가 여러 개인지 체크
    if (email.find('@', at_pos + 1) != std::string::npos) {
        return std::make_tuple(false, "@ 기호가 여러 개 있습니다.");
    }
    
    // 로컬 파트와 도메인 파트 분리
    std::string local_part = email.substr(0, at_pos);
    std::string domain_part = email.substr(at_pos + 1);
    
    // 로컬 파트 체크
    if (local_part.empty()) {
        return std::make_tuple(false, "로컬 파트가 비어 있습니다.");
    }
    
    if (local_part.length() > 64) {
        return std::make_tuple(false, "로컬 파트가 너무 깁니다 (64자 초과).");
    }
    
    // 로컬 파트 시작과 끝이 점(.)인지 체크
    if (local_part.front() == '.') {
        return std::make_tuple(false, "로컬 파트가 점(.)으로 시작할 수 없습니다.");
    }
    
    if (local_part.back() == '.') {
        return std::make_tuple(false, "로컬 파트가 점(.)으로 끝날 수 없습니다.");
    }
    
    // 로컬 파트에 연속된 점(..)이 있는지 체크
    if (local_part.find("..") != std::string::npos) {
        return std::make_tuple(false, "로컬 파트에 연속된 점(..)이 있습니다.");
    }
    
    // 도메인 파트 체크
    if (domain_part.empty()) {
        return std::make_tuple(false, "도메인 파트가 비어 있습니다.");
    }
    
    // 도메인 파트 시작과 끝이 점(.)인지 체크
    if (domain_part.front() == '.') {
        return std::make_tuple(false, "도메인 파트가 점(.)으로 시작할 수 없습니다.");
    }
    
    if (domain_part.back() == '.') {
        return std::make_tuple(false, "도메인 파트가 점(.)으로 끝날 수 없습니다.");
    }
    
    // 도메인 파트에 연속된 점(..)이 있는지 체크
    if (domain_part.find("..") != std::string::npos) {
        return std::make_tuple(false, "도메인 파트에 연속된 점(..)이 있습니다.");
    }
    
    // 도메인 파트에 유효하지 않은 문자가 있는지 체크
    for (char c : domain_part) {
        if (!(std::isalnum(static_cast<unsigned char>(c)) || c == '.' || c == '-')) {
            return std::make_tuple(false, "도메인 파트에 유효하지 않은 문자가 있습니다.");
        }
    }
    
    // 도메인 파트에 점(.)이 최소 하나 있는지 체크
    if (domain_part.find('.') == std::string::npos) {
        return std::make_tuple(false, "도메인 파트에 점(.)이 없습니다.");
    }
    
    // 최상위 도메인(TLD) 체크
    size_t last_dot = domain_part.find_last_of('.');
    std::string tld = domain_part.substr(last_dot + 1);
    
    if (tld.empty()) {
        return std::make_tuple(false, "최상위 도메인이 비어 있습니다.");
    }
    
    if (tld.length() < 2) {
        return std::make_tuple(false, "최상위 도메인이 너무 짧습니다 (최소 2자).");
    }
    
    // TLD가 알파벳만으로 구성되었는지 체크
    for (char c : tld) {
        if (!std::isalpha(static_cast<unsigned char>(c))) {
            return std::make_tuple(false, "최상위 도메인에 알파벳이 아닌 문자가 있습니다.");
        }
    }
    
    // 로컬 파트에 유효한 문자만 있는지 체크 (더 유연한 검사)
    // 로컬 파트는 알파벳, 숫자, 특수문자 !#$%&'*+-/=?^_`{|}~.를 포함할 수 있음
    // 또한 따옴표로 둘러싸인 부분에는 더 많은 문자를 허용할 수 있음
    bool in_quotes = false;
    bool escape_next = false;
    
    for (size_t i = 0; i < local_part.length(); ++i) {
        char c = local_part[i];
        
        if (escape_next) {
            escape_next = false;
            continue;
        }
        
        if (c == '\\') {
            escape_next = true;
            continue;
        }
        
        if (c == '"') {
            in_quotes = !in_quotes;
            continue;
        }
        
        if (in_quotes) {
            // 따옴표 안에서는 대부분의 문자 허용 (null, CR, LF 제외)
            if (c == 0 || c == '\r' || c == '\n') {
                return std::make_tuple(false, "로컬 파트에 허용되지 않은 제어 문자가 있습니다.");
            }
            continue;
        }
        
        // 따옴표 밖에서 허용되는 문자
        if (!(std::isalnum(static_cast<unsigned char>(c)) || 
              c == '!' || c == '#' || c == '$' || c == '%' || c == '&' || 
              c == '\'' || c == '*' || c == '+' || c == '-' || c == '/' || 
              c == '=' || c == '?' || c == '^' || c == '_' || c == '`' || 
              c == '{' || c == '}' || c == '|' || c == '~' || c == '.')) {
            return std::make_tuple(false, "로컬 파트에 유효하지 않은 문자가 있습니다.");
        }
    }
    
    // 따옴표가 제대로 닫혔는지 체크
    if (in_quotes) {
        return std::make_tuple(false, "로컬 파트의 따옴표가 제대로 닫히지 않았습니다.");
    }
    
    // 정규식을 사용한 최종 검증 (더 포괄적인 패턴)
    // 이 패턴은 RFC 5322를 완전히 준수하지는 않지만 일반적인 이메일 주소를 커버함
    std::regex email_pattern(
        R"(^[a-zA-Z0-9.!#$%&'*+/=?^_`{|}~-]+@[a-zA-Z0-9](?:[a-zA-Z0-9-]{0,61}[a-zA-Z0-9])?(?:\.[a-zA-Z0-9](?:[a-zA-Z0-9-]{0,61}[a-zA-Z0-9])?)*$)"
    );
    
    if (!std::regex_match(email, email_pattern)) {
        return std::make_tuple(false, "이메일 주소 형식이 유효하지 않습니다.");
    }
    
    // 모든 검사를 통과한 경우
    return std::make_tuple(true, "유효한 이메일 주소입니다.");
}