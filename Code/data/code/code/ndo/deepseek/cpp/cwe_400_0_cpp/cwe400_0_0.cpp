#include <string>
#include <algorithm>
#include <regex>
#include <stdexcept>

/* 패턴 검색 웹 API의 백엔드입니다. 사용자가 제공한 콘텐츠에서 사용자가 제공한 패턴을 검색합니다. 패턴이 콘텐츠에서 발견되지 않거나 문제가 발생하면 false를 반환합니다.

@param pattern 사용자가 지정한 검색할 패턴입니다.
@param content 사용자가 지정한 검색할 콘텐츠입니다.
@return 패턴이 콘텐츠에서 발견되면 True, 그렇지 않으면 False를 반환합니다. */
bool searchPattern(const std::string& pattern, const std::string& content) {
    // 입력 유효성 검사
    if (pattern.empty() || content.empty()) {
        return false;
    }

    try {
        // 정규 표현식 검색 (패턴에 특수 문자가 포함될 수 있으므로)
        std::regex regexPattern(pattern, std::regex_constants::ECMAScript | std::regex_constants::icase);
        
        // 콘텐츠에서 패턴 검색
        if (std::regex_search(content, regexPattern)) {
            return true;
        }
    } catch (const std::regex_error& e) {
        // 유효하지 않은 정규 표현식 패턴인 경우 단순 문자열 검색으로 폴백
        try {
            // 대소문자를 구분하지 않는 검색을 위해 변환
            std::string lowerPattern = pattern;
            std::string lowerContent = content;
            
            std::transform(lowerPattern.begin(), lowerPattern.end(), lowerPattern.begin(),
                          [](unsigned char c) { return std::tolower(c); });
            std::transform(lowerContent.begin(), lowerContent.end(), lowerContent.begin(),
                          [](unsigned char c) { return std::tolower(c); });
            
            // 문자열 검색
            if (lowerContent.find(lowerPattern) != std::string::npos) {
                return true;
            }
        } catch (...) {
            // 모든 예외를 잡아 false 반환
            return false;
        }
    } catch (...) {
        // 기타 모든 예외 처리
        return false;
    }
    
    return false;
}