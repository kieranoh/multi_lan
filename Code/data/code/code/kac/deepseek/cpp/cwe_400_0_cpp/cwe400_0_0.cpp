#include <string>
#include <algorithm>
#include <regex>

bool searchPattern(const std::string& pattern, const std::string& content) {
    // 입력 유효성 검사: 패턴이나 콘텐츠가 비어있으면 false 반환
    if (pattern.empty() || content.empty()) {
        return false;
    }
    
    try {
        // 정규 표현식으로 패턴 검색 (대소문자 구분)
        std::regex regexPattern(pattern);
        return std::regex_search(content, regexPattern);
    } catch (const std::regex_error& e) {
        // 잘못된 정규 표현식 패턴인 경우 false 반환
        return false;
    } catch (...) {
        // 기타 예외 처리
        return false;
    }
}