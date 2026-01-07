#include <string>
#include <algorithm>
#include <regex>

bool searchPattern(const std::string& pattern, const std::string& content) {
    // 빈 패턴은 항상 false 반환
    if (pattern.empty()) {
        return false;
    }
    
    // 빈 콘텐츠에서 패턴 검색은 항상 false 반환
    if (content.empty()) {
        return false;
    }
    
    try {
        // 정규 표현식으로 패턴 검색 시도
        std::regex regexPattern(pattern);
        return std::regex_search(content, regexPattern);
    } catch (const std::regex_error& e) {
        // 정규 표현식 오류 발생 시 단순 문자열 검색으로 폴백
        return content.find(pattern) != std::string::npos;
    } catch (...) {
        // 기타 모든 예외 처리
        return false;
    }
}