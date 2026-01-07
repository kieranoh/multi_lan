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
    
    // 길이 체크 (RFC 5321에 따르면 로컬 파트는 64자, 도메인 파트는 255자까지 가능)
    if (email.length() > 254) {
        return std::make_tuple(false, "이메일 주소가 너무 깁니다 (최대 254자).");
    }
    
    // @ 기호 체크
    size_t at_pos = email.find('@');
    if (at_pos == std::string::npos) {
        return std::make_tuple(false, "@ 기호가 없습니다.");
    }
    
    // @ 기호가 여러 개 있는지 체크
    if (email.find('@', at_pos + 1) != std::string::npos) {
        return std::make_tuple(false, "@ 기호가 여러 개 있습니다.");
    }
    
    // 로컬 파트와 도메인 파트 분리
    std::string local_part = email.substr(0, at_pos);
    std::string domain_part = email.substr(at_pos + 1);
    
    // 로컬 파트와 도메인 파트가 비어있는지 체크
    if (local_part.empty()) {
        return std::make_tuple(false, "로컬 파트가 비어 있습니다.");
    }
    if (domain_part.empty()) {
        return std::make_tuple(false, "도메인 파트가 비어 있습니다.");
    }
    
    // 로컬 파트 길이 체크
    if (local_part.length() > 64) {
        return std::make_tuple(false, "로컬 파트가 너무 깁니다 (최대 64자).");
    }
    
    // 도메인 파트 길이 체크
    if (domain_part.length() > 255) {
        return std::make_tuple(false, "도메인 파트가 너무 깁니다 (최대 255자).");
    }
    
    // 로컬 파트의 시작과 끝이 마침표인지 체크
    if (local_part.front() == '.') {
        return std::make_tuple(false, "로컬 파트가 마침표로 시작할 수 없습니다.");
    }
    if (local_part.back() == '.') {
        return std::make_tuple(false, "로컬 파트가 마침표로 끝날 수 없습니다.");
    }
    
    // 연속된 마침표 체크
    if (local_part.find("..") != std::string::npos) {
        return std::make_tuple(false, "로컬 파트에 연속된 마침표가 있습니다.");
    }
    
    // 도메인 파트의 시작과 끝이 마침표나 하이픈인지 체크
    if (domain_part.front() == '.' || domain_part.front() == '-') {
        return std::make_tuple(false, "도메인 파트가 마침표나 하이픈으로 시작할 수 없습니다.");
    }
    if (domain_part.back() == '.' || domain_part.back() == '-') {
        return std::make_tuple(false, "도메인 파트가 마침표나 하이픈으로 끝날 수 없습니다.");
    }
    
    // 도메인 파트에 연속된 마침표나 하이픈 체크
    if (domain_part.find("..") != std::string::npos || domain_part.find("--") != std::string::npos) {
        return std::make_tuple(false, "도메인 파트에 연속된 마침표나 하이픈이 있습니다.");
    }
    
    // 도메인 파트에 유효한 문자만 있는지 체크
    for (char c : domain_part) {
        if (!std::isalnum(static_cast<unsigned char>(c)) && c != '.' && c != '-') {
            return std::make_tuple(false, "도메인 파트에 유효하지 않은 문자가 있습니다: " + std::string(1, c));
        }
    }
    
    // 최소한 하나의 마침표가 있는지 체크 (최상위 도메인)
    if (domain_part.find('.') == std::string::npos) {
        return std::make_tuple(false, "도메인 파트에 마침표가 없습니다 (최상위 도메인 필요).");
    }
    
    // 도메인 레이블 체크 (각 레이블은 1-63자, 알파벳/숫자/하이픈만 가능, 시작과 끝이 하이픈이면 안됨)
    size_t start = 0;
    size_t dot_pos;
    do {
        dot_pos = domain_part.find('.', start);
        std::string label = (dot_pos == std::string::npos) ? 
                           domain_part.substr(start) : 
                           domain_part.substr(start, dot_pos - start);
        
        if (label.empty()) {
            return std::make_tuple(false, "도메인 레이블이 비어 있습니다.");
        }
        
        if (label.length() > 63) {
            return std::make_tuple(false, "도메인 레이블이 너무 깁니다 (최대 63자): " + label);
        }
        
        if (label.front() == '-') {
            return std::make_tuple(false, "도메인 레이블이 하이픈으로 시작할 수 없습니다: " + label);
        }
        
        if (label.back() == '-') {
            return std::make_tuple(false, "도메인 레이블이 하이픈으로 끝날 수 없습니다: " + label);
        }
        
        for (char c : label) {
            if (!std::isalnum(static_cast<unsigned char>(c)) && c != '-') {
                return std::make_tuple(false, "도메인 레이블에 유효하지 않은 문자가 있습니다: " + std::string(1, c) + " in " + label);
            }
        }
        
        start = dot_pos + 1;
    } while (dot_pos != std::string::npos);
    
    // 로컬 파트에 유효한 문자만 있는지 체크 (더 유연한 규칙 적용)
    for (size_t i = 0; i < local_part.length(); ++i) {
        char c = local_part[i];
        // 허용되는 문자: 알파벳, 숫자, 특수문자 !#$%&'*+-/=?^_`{|}~.
        if (!std::isalnum(static_cast<unsigned char>(c)) && 
            c != '!' && c != '#' && c != '$' && c != '%' && c != '&' && 
            c != '\'' && c != '*' && c != '+' && c != '-' && c != '/' && 
            c != '=' && c != '?' && c != '^' && c != '_' && c != '`' && 
            c != '{' && c != '|' && c != '}' && c != '~' && c != '.') {
            // 따옴표로 묶인 부분은 더 많은 문자를 허용할 수 있지만, 여기서는 간단하게 처리
            return std::make_tuple(false, "로컬 파트에 유효하지 않은 문자가 있습니다: " + std::string(1, c));
        }
    }
    
    // 모든 검사를 통과한 경우
    return std::make_tuple(true, "유효한 이메일 주소입니다.");
}