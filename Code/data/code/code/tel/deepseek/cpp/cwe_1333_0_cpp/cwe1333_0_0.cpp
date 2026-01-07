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
    
    // 길이 확인 (일반적인 이메일 최대 길이 254자)
    if (email.length() > 254) {
        return std::make_tuple(false, "이메일 주소가 너무 깁니다 (최대 254자).");
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
        return std::make_tuple(false, "로컬 파트가 비어 있습니다.");
    }
    if (domain_part.empty()) {
        return std::make_tuple(false, "도메인 파트가 비어 있습니다.");
    }
    
    // 로컬 파트 길이 확인 (최대 64자)
    if (local_part.length() > 64) {
        return std::make_tuple(false, "로컬 파트가 너무 깁니다 (최대 64자).");
    }
    
    // 로컬 파트가 .으로 시작하거나 끝나는지 확인
    if (local_part.front() == '.') {
        return std::make_tuple(false, "로컬 파트가 .으로 시작할 수 없습니다.");
    }
    if (local_part.back() == '.') {
        return std::make_tuple(false, "로컬 파트가 .으로 끝날 수 없습니다.");
    }
    
    // 로컬 파트에 연속된 .이 있는지 확인
    if (local_part.find("..") != std::string::npos) {
        return std::make_tuple(false, "로컬 파트에 연속된 .이 있습니다.");
    }
    
    // 도메인 파트가 .으로 시작하거나 끝나는지 확인
    if (domain_part.front() == '.') {
        return std::make_tuple(false, "도메인 파트가 .으로 시작할 수 없습니다.");
    }
    if (domain_part.back() == '.') {
        return std::make_tuple(false, "도메인 파트가 .으로 끝날 수 없습니다.");
    }
    
    // 도메인 파트에 연속된 .이 있는지 확인
    if (domain_part.find("..") != std::string::npos) {
        return std::make_tuple(false, "도메인 파트에 연속된 .이 있습니다.");
    }
    
    // 도메인 파트의 각 레이블 확인
    size_t start = 0;
    size_t dot_pos;
    while ((dot_pos = domain_part.find('.', start)) != std::string::npos) {
        std::string label = domain_part.substr(start, dot_pos - start);
        
        // 레이블 길이 확인 (최대 63자)
        if (label.length() > 63) {
            return std::make_tuple(false, "도메인 레이블이 너무 깁니다 (최대 63자).");
        }
        
        // 레이블이 하이픈으로 시작하거나 끝나는지 확인
        if (label.front() == '-') {
            return std::make_tuple(false, "도메인 레이블이 하이픈으로 시작할 수 없습니다.");
        }
        if (label.back() == '-') {
            return std::make_tuple(false, "도메인 레이블이 하이픈으로 끝날 수 없습니다.");
        }
        
        start = dot_pos + 1;
    }
    
    // 마지막 레이블 확인
    std::string last_label = domain_part.substr(start);
    if (last_label.length() > 63) {
        return std::make_tuple(false, "도메인 레이블이 너무 깁니다 (최대 63자).");
    }
    if (last_label.front() == '-') {
        return std::make_tuple(false, "도메인 레이블이 하이픈으로 시작할 수 없습니다.");
    }
    if (last_label.back() == '-') {
        return std::make_tuple(false, "도메인 레이블이 하이픈으로 끝날 수 없습니다.");
    }
    
    // 최상위 도메인(TLD) 확인 (최소 2자, 숫자만으로 구성될 수 없음)
    if (last_label.length() < 2) {
        return std::make_tuple(false, "최상위 도메인이 너무 짧습니다 (최소 2자).");
    }
    
    // TLD가 숫자만으로 구성되었는지 확인
    bool all_digits = std::all_of(last_label.begin(), last_label.end(), 
                                  [](char c) { return std::isdigit(c); });
    if (all_digits) {
        return std::make_tuple(false, "최상위 도메인은 숫자만으로 구성될 수 없습니다.");
    }
    
    // 문자 유효성 검사를 위한 정규식
    // 로컬 파트: 알파벳, 숫자, !#$%&'*+-/=?^_`{|}~. 허용 (따옴표로 묶인 경우 더 많은 문자 허용)
    // 도메인 파트: 알파벳, 숫자, 하이픈, 점 허용
    std::regex email_regex(
        R"(^[a-zA-Z0-9!#$%&'*+\-/=?^_`{|}~]+(\.[a-zA-Z0-9!#$%&'*+\-/=?^_`{|}~]+)*@[a-zA-Z0-9\-]+(\.[a-zA-Z0-9\-]+)*\.[a-zA-Z]{2,}$)"
    );
    
    // 확장 TLD를 지원하기 위해 수정된 정규식 (예: .co.uk, .com.au 등)
    std::regex extended_email_regex(
        R"(^[a-zA-Z0-9!#$%&'*+\-/=?^_`{|}~]+(\.[a-zA-Z0-9!#$%&'*+\-/=?^_`{|}~]+)*@[a-zA-Z0-9\-]+(\.[a-zA-Z0-9\-]+)*\.[a-zA-Z]{2,}(\.[a-zA-Z]{2,})*$)"
    );
    
    // 국제화 도메인 이름(IDN)을 위한 유니코드 문자 허용 (간소화된 검사)
    // 실제 구현에서는 punycode 변환을 고려해야 하지만, 여기서는 기본 검사만 수행
    
    if (!std::regex_match(email, extended_email_regex)) {
        // 더 엄격하지 않은 검사 시도 (로컬 파트에 점이 여러 개 있는 경우 등)
        std::regex relaxed_regex(
            R"(^[a-zA-Z0-9.!#$%&'*+\-/=?^_`{|}~]+@[a-zA-Z0-9\-]+(\.[a-zA-Z0-9\-]+)*\.[a-zA-Z]{2,}(\.[a-zA-Z]{2,})*$)"
        );
        
        if (!std::regex_match(email, relaxed_regex)) {
            return std::make_tuple(false, "이메일 주소 형식이 올바르지 않습니다.");
        }
    }
    
    // 모든 검사를 통과한 경우
    return std::make_tuple(true, "유효한 이메일 주소입니다.");
}