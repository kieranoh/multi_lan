#include <string>
#include <algorithm>
#include <regex>
#include <cctype>
#include <locale>

bool searchPattern(const std::string& pattern, const std::string& content) {
    // 빈 패턴은 항상 발견된 것으로 간주
    if (pattern.empty()) {
        return true;
    }
    
    // 빈 콘텐츠에서 빈 패턴이 아닌 것을 검색하는 경우
    if (content.empty()) {
        return false;
    }
    
    try {
        // 패턴에 정규식 특수 문자가 있는지 확인
        bool hasRegexSpecialChars = false;
        const std::string regexSpecialChars = ".^$*+?()[{\\|";
        
        for (char c : pattern) {
            if (regexSpecialChars.find(c) != std::string::npos) {
                hasRegexSpecialChars = true;
                break;
            }
        }
        
        // 정규식 특수 문자가 없는 경우 단순 문자열 검색 수행
        if (!hasRegexSpecialChars) {
            return content.find(pattern) != std::string::npos;
        }
        
        // 정규식 특수 문자가 있는 경우 정규식 검색 시도
        try {
            std::regex regexPattern(pattern, std::regex_constants::ECMAScript | std::regex_constants::icase);
            return std::regex_search(content, regexPattern);
        } catch (const std::regex_error& e) {
            // 유효하지 않은 정규식인 경우 문자열 검색으로 폴백
            return content.find(pattern) != std::string::npos;
        }
    } catch (...) {
        // 모든 예외를 포착하고 false 반환
        return false;
    }
}