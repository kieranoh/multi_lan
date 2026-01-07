#include <string>
#include <algorithm>
#include <regex>

bool searchPattern(const std::string& pattern, const std::string& content) {
    // 빈 패턴은 항상 발견된 것으로 간주
    if (pattern.empty()) {
        return true;
    }
    
    // 빈 콘텐츠에서 빈이 아닌 패턴을 검색하는 경우
    if (content.empty()) {
        return false;
    }
    
    try {
        // 패턴에 정규식 특수 문자가 포함되어 있는지 확인
        // 단순 문자열 검색과 정규식 검색을 모두 지원
        bool hasRegexSpecialChars = false;
        const std::string regexSpecialChars = ".^$*+?()[{\\|";
        
        for (char c : pattern) {
            if (regexSpecialChars.find(c) != std::string::npos) {
                hasRegexSpecialChars = true;
                break;
            }
        }
        
        if (hasRegexSpecialChars) {
            // 정규식으로 검색 시도
            std::regex regexPattern;
            try {
                regexPattern = std::regex(pattern);
            } catch (const std::regex_error&) {
                // 유효하지 않은 정규식인 경우 일반 문자열 검색으로 폴백
                return content.find(pattern) != std::string::npos;
            }
            
            return std::regex_search(content, regexPattern);
        } else {
            // 일반 문자열 검색 (더 빠름)
            return content.find(pattern) != std::string::npos;
        }
    } catch (...) {
        // 모든 예외를 잡아 false 반환
        return false;
    }
}