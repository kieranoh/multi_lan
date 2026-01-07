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
    
    // 길이 체크 (일반적인 이메일 최대 길이 254자)
    if (email.length() > 254) {
        return std::make_tuple(false, "이메일 주소가 너무 깁니다 (최대 254자).");
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
    
    // 로컬 파트와 도메인 파트가 비어있는지 체크
    if (local_part.empty()) {
        return std::make_tuple(false, "로컬 파트(사용자 이름)가 비어 있습니다.");
    }
    if (domain_part.empty()) {
        return std::make_tuple(false, "도메인 파트가 비어 있습니다.");
    }
    
    // 로컬 파트 길이 체크 (최대 64자)
    if (local_part.length() > 64) {
        return std::make_tuple(false, "로컬 파트가 너무 깁니다 (최대 64자).");
    }
    
    // 로컬 파트 시작과 끝이 점(.)인지 체크
    if (local_part.front() == '.') {
        return std::make_tuple(false, "로컬 파트가 점(.)으로 시작할 수 없습니다.");
    }
    if (local_part.back() == '.') {
        return std::make_tuple(false, "로컬 파트가 점(.)으로 끝날 수 없습니다.");
    }
    
    // 연속된 점(..) 체크
    if (local_part.find("..") != std::string::npos) {
        return std::make_tuple(false, "로컬 파트에 연속된 점(..)이 있습니다.");
    }
    
    // 도메인 파트 시작과 끝이 점(.)인지 체크
    if (domain_part.front() == '.') {
        return std::make_tuple(false, "도메인 파트가 점(.)으로 시작할 수 없습니다.");
    }
    if (domain_part.back() == '.') {
        return std::make_tuple(false, "도메인 파트가 점(.)으로 끝날 수 없습니다.");
    }
    
    // 도메인 파트에 연속된 점(..) 체크
    if (domain_part.find("..") != std::string::npos) {
        return std::make_tuple(false, "도메인 파트에 연속된 점(..)이 있습니다.");
    }
    
    // 도메인 파트에 유효한 문자만 있는지 체크
    for (char c : domain_part) {
        if (!std::isalnum(static_cast<unsigned char>(c)) && c != '.' && c != '-') {
            return std::make_tuple(false, "도메인 파트에 유효하지 않은 문자가 있습니다: " + std::string(1, c));
        }
    }
    
    // 도메인 레이블 체크
    size_t dot_pos = 0;
    size_t prev_pos = 0;
    while ((dot_pos = domain_part.find('.', prev_pos)) != std::string::npos) {
        std::string label = domain_part.substr(prev_pos, dot_pos - prev_pos);
        
        // 레이블 길이 체크 (최대 63자)
        if (label.length() > 63) {
            return std::make_tuple(false, "도메인 레이블이 너무 깁니다 (최대 63자).");
        }
        
        // 레이블 시작과 끝이 하이픈(-)인지 체크
        if (label.front() == '-') {
            return std::make_tuple(false, "도메인 레이블이 하이픈(-)으로 시작할 수 없습니다.");
        }
        if (label.back() == '-') {
            return std::make_tuple(false, "도메인 레이블이 하이픈(-)으로 끝날 수 없습니다.");
        }
        
        // 레이블이 비어있는지 체크
        if (label.empty()) {
            return std::make_tuple(false, "도메인에 빈 레이블이 있습니다.");
        }
        
        prev_pos = dot_pos + 1;
    }
    
    // 마지막 레이블 체크
    std::string last_label = domain_part.substr(prev_pos);
    if (last_label.length() > 63) {
        return std::make_tuple(false, "도메인 레이블이 너무 깁니다 (최대 63자).");
    }
    if (last_label.front() == '-') {
        return std::make_tuple(false, "도메인 레이블이 하이픈(-)으로 시작할 수 없습니다.");
    }
    if (last_label.back() == '-') {
        return std::make_tuple(false, "도메인 레이블이 하이픈(-)으로 끝날 수 없습니다.");
    }
    if (last_label.empty()) {
        return std::make_tuple(false, "도메인에 빈 레이블이 있습니다.");
    }
    
    // 최상위 도메인(TLD) 체크 (최소 2자, 숫자만으로 구성되지 않음)
    if (last_label.length() < 2) {
        return std::make_tuple(false, "최상위 도메인(TLD)은 최소 2자 이상이어야 합니다.");
    }
    
    bool all_digits = true;
    for (char c : last_label) {
        if (!std::isdigit(static_cast<unsigned char>(c))) {
            all_digits = false;
            break;
        }
    }
    if (all_digits) {
        return std::make_tuple(false, "최상위 도메인(TLD)은 숫자만으로 구성될 수 없습니다.");
    }
    
    // 로컬 파트에 유효한 문자만 있는지 체크 (더 유연한 검사)
    // 이메일 표준(RFC 5322)에 따르면 로컬 파트는 더 많은 특수 문자를 허용하지만,
    // 여기서는 일반적인 사용 사례를 다루기 위해 제한된 집합을 사용합니다.
    for (char c : local_part) {
        if (!std::isalnum(static_cast<unsigned char>(c)) && c != '.' && c != '!' && 
            c != '#' && c != '$' && c != '%' && c != '&' && c != '\'' && 
            c != '*' && c != '+' && c != '-' && c != '/' && c != '=' && 
            c != '?' && c != '^' && c != '_' && c != '`' && c != '{' && 
            c != '|' && c != '}' && c != '~') {
            return std::make_tuple(false, "로컬 파트에 유효하지 않은 문자가 있습니다: " + std::string(1, c));
        }
    }
    
    // 모든 검사를 통과한 경우
    return std::make_tuple(true, "유효한 이메일 주소입니다.");
}