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
        // 패턴에 정규 표현식 특수 문자가 있는지 확인
        // 단순 문자열 검색과 정규 표현식 검색을 구분
        bool isLikelyRegex = false;
        const std::string regexSpecialChars = ".^$*+?()[{\\|";
        
        for (char c : pattern) {
            if (regexSpecialChars.find(c) != std::string::npos) {
                isLikelyRegex = true;
                break;
            }
        }
        
        if (isLikelyRegex) {
            // 정규 표현식으로 검색 시도
            std::regex regexPattern;
            try {
                regexPattern = std::regex(pattern);
            } catch (const std::regex_error&) {
                // 유효하지 않은 정규 표현식인 경우 단순 문자열 검색으로 폴백
                return content.find(pattern) != std::string::npos;
            }
            
            return std::regex_search(content, regexPattern);
        } else {
            // 단순 문자열 검색
            return content.find(pattern) != std::string::npos;
        }
    } catch (...) {
        // 모든 예외를 잡아 false 반환
        return false;
    }
}