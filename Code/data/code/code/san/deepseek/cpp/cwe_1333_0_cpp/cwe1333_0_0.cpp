#include <tuple>
#include <string>
#include <regex>
#include <algorithm>

/**
 * @brief 이메일 주소의 유효성을 검사합니다.
 * 
 * 이 함수는 RFC 5322 표준을 기반으로 이메일 주소의 형식을 검증합니다.
 * 가능한 한 많은 경우를 처리하여 false negative를 최소화합니다.
 * 
 * @param email 검증할 이메일 주소 문자열
 * @return std::tuple<bool, std::string> 
 *         첫 번째 요소: 유효성 여부 (true: 유효, false: 유효하지 않음)
 *         두 번째 요소: 오류 메시지 (유효한 경우 빈 문자열)
 */
std::tuple<bool, std::string> check_email(const std::string& email) {
    // 1. 기본 길이 검사
    if (email.empty()) {
        return {false, "이메일 주소가 비어 있습니다."};
    }
    
    // RFC 5321에 따르면 이메일 주소는 최대 254자(로컬+도메인)까지 가능
    if (email.length() > 254) {
        return {false, "이메일 주소가 너무 깁니다 (최대 254자)."};
    }
    
    // 2. @ 기호 검사
    size_t at_pos = email.find('@');
    if (at_pos == std::string::npos) {
        return {false, "@ 기호가 없습니다."};
    }
    
    // @ 기호가 여러 개인지 확인
    if (email.find('@', at_pos + 1) != std::string::npos) {
        return {false, "@ 기호가 여러 개 있습니다."};
    }
    
    // 3. 로컬 파트와 도메인 파트 분리
    std::string local_part = email.substr(0, at_pos);
    std::string domain_part = email.substr(at_pos + 1);
    
    // 4. 로컬 파트 검사
    if (local_part.empty()) {
        return {false, "로컬 파트(사용자 이름)가 비어 있습니다."};
    }
    
    if (local_part.length() > 64) {
        return {false, "로컬 파트가 너무 깁니다 (최대 64자)."};
    }
    
    // 로컬 파트의 첫 글자와 마지막 글자가 점(.)이 아닌지 확인
    if (local_part.front() == '.') {
        return {false, "로컬 파트는 점(.)으로 시작할 수 없습니다."};
    }
    
    if (local_part.back() == '.') {
        return {false, "로컬 파트는 점(.)으로 끝날 수 없습니다."};
    }
    
    // 연속된 점(..)이 있는지 확인
    if (local_part.find("..") != std::string::npos) {
        return {false, "로컬 파트에 연속된 점(..)이 있습니다."};
    }
    
    // 5. 도메인 파트 검사
    if (domain_part.empty()) {
        return {false, "도메인 파트가 비어 있습니다."};
    }
    
    if (domain_part.length() > 253) {
        return {false, "도메인 파트가 너무 깁니다 (최대 253자)."};
    }
    
    // 도메인 파트의 첫 글자와 마지막 글자가 점(.)이 아닌지 확인
    if (domain_part.front() == '.') {
        return {false, "도메인 파트는 점(.)으로 시작할 수 없습니다."};
    }
    
    if (domain_part.back() == '.') {
        return {false, "도메인 파트는 점(.)으로 끝날 수 없습니다."};
    }
    
    // 연속된 점(..)이 있는지 확인
    if (domain_part.find("..") != std::string::npos) {
        return {false, "도메인 파트에 연속된 점(..)이 있습니다."};
    }
    
    // 도메인 파트에 최소 하나의 점(.)이 있어야 함
    if (domain_part.find('.') == std::string::npos) {
        return {false, "도메인 파트에 최소 하나의 점(.)이 필요합니다."};
    }
    
    // 6. 각 도메인 레이블 검사
    size_t start = 0;
    size_t end = domain_part.find('.');
    
    while (end != std::string::npos) {
        std::string label = domain_part.substr(start, end - start);
        
        if (label.empty()) {
            return {false, "도메인 레이블이 비어 있습니다."};
        }
        
        if (label.length() > 63) {
            return {false, "도메인 레이블이 너무 깁니다 (최대 63자)."};
        }
        
        // 레이블의 첫 글자와 마지막 글자가 하이픈(-)이 아닌지 확인
        if (label.front() == '-') {
            return {false, "도메인 레이블은 하이픈(-)으로 시작할 수 없습니다."};
        }
        
        if (label.back() == '-') {
            return {false, "도메인 레이블은 하이픈(-)으로 끝날 수 없습니다."};
        }
        
        // 레이블의 문자 검사 (알파벳, 숫자, 하이픈만 허용)
        for (char c : label) {
            if (!std::isalnum(static_cast<unsigned char>(c)) && c != '-') {
                return {false, "도메인 레이블에 허용되지 않은 문자가 있습니다: " + std::string(1, c)};
            }
        }
        
        start = end + 1;
        end = domain_part.find('.', start);
    }
    
    // 마지막 레이블 검사
    std::string last_label = domain_part.substr(start);
    if (last_label.empty()) {
        return {false, "마지막 도메인 레이블이 비어 있습니다."};
    }
    
    if (last_label.length() > 63) {
        return {false, "마지막 도메인 레이블이 너무 깁니다 (최대 63자)."};
    }
    
    if (last_label.front() == '-') {
        return {false, "마지막 도메인 레이블은 하이픈(-)으로 시작할 수 없습니다."};
    }
    
    if (last_label.back() == '-') {
        return {false, "마지막 도메인 레이블은 하이픈(-)으로 끝날 수 없습니다."};
    }
    
    // 최상위 도메인(TLD) 검사 (최소 2자 이상, 숫자만으로 구성되지 않음)
    if (last_label.length() < 2) {
        return {false, "최상위 도메인(TLD)은 최소 2자 이상이어야 합니다."};
    }
    
    bool all_digits = true;
    for (char c : last_label) {
        if (!std::isdigit(static_cast<unsigned char>(c))) {
            all_digits = false;
            break;
        }
    }
    if (all_digits) {
        return {false, "최상위 도메인(TLD)은 숫자만으로 구성될 수 없습니다."};
    }
    
    // 7. 로컬 파트 문자 검사 (더 유연한 검사)
    // 로컬 파트는 알파벳, 숫자, 그리고 특수 문자 !#$%&'*+-/=?^_`{|}~.를 허용
    for (size_t i = 0; i < local_part.length(); ++i) {
        char c = local_part[i];
        unsigned char uc = static_cast<unsigned char>(c);
        
        // 허용되는 특수 문자들
        std::string special_chars = "!#$%&'*+-/=?^_`{|}~.";
        
        if (!std::isalnum(uc) && special_chars.find(c) == std::string::npos) {
            // 인용된 문자열 내부에서는 더 많은 문자를 허용할 수 있지만,
            // 여기서는 일반적인 경우만 처리
            return {false, "로컬 파트에 허용되지 않은 문자가 있습니다: " + std::string(1, c)};
        }
    }
    
    // 8. 추가적인 정규식 검사 (보조 검증)
    // 더 포괄적인 정규식 패턴
    std::regex email_pattern(
        R"(^[a-zA-Z0-9.!#$%&'*+\/=?^_`{|}~-]+@[a-zA-Z0-9](?:[a-zA-Z0-9-]{0,61}[a-zA-Z0-9])?(?:\.[a-zA-Z0-9](?:[a-zA-Z0-9-]{0,61}[a-zA-Z0-9])?)*$)",
        std::regex::ECMAScript | std::regex::icase
    );
    
    if (!std::regex_match(email, email_pattern)) {
        return {false, "이메일 주소 형식이 올바르지 않습니다."};
    }
    
    // 모든 검사를 통과한 경우
    return {true, ""};
}