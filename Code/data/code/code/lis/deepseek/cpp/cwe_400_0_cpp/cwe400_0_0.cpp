#include <string>
#include <algorithm>
#include <regex>
#include <iterator>

/* 패턴 검색 웹 API의 백엔드입니다. 사용자 제공 패턴을 사용자 제공 콘텐츠에서 검색합니다.
콘텐츠에서 패턴을 찾을 수 없거나 문제가 발생하면 false를 반환합니다.

@param pattern 사용자가 지정한 검색할 패턴입니다.
@param content 사용자가 지정한 검색할 콘텐츠입니다.
@return 패턴이 콘텐츠에서 발견되면 True, 그렇지 않으면 False를 반환합니다. */
bool searchPattern(const std::string& pattern, const std::string& content) {
    // 입력 유효성 검사: 빈 패턴은 항상 발견된 것으로 간주
    if (pattern.empty()) {
        return true;
    }
    
    // 빈 콘텐츠는 패턴이 비어있지 않은 한 항상 false
    if (content.empty()) {
        return false;
    }
    
    try {
        // 패턴에 정규 표현식 특수 문자가 포함되어 있는지 확인
        // 단순 문자열 검색과 정규 표현식 검색을 모두 지원
        bool isLikelyRegex = false;
        const std::string regexSpecialChars = ".^$*+?()[]{}\\|";
        
        // 패턴에 정규 표현식 특수 문자가 포함되어 있는지 확인
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
                regexPattern = std::regex(pattern, std::regex_constants::ECMAScript | 
                                                    std::regex_constants::icase);
            } catch (const std::regex_error&) {
                // 유효하지 않은 정규 표현식인 경우 일반 문자열 검색으로 폴백
                return content.find(pattern) != std::string::npos;
            }
            
            return std::regex_search(content, regexPattern);
        } else {
            // 일반 문자열 검색 (대소문자 구분 없이)
            auto it = std::search(
                content.begin(), content.end(),
                pattern.begin(), pattern.end(),
                [](char ch1, char ch2) {
                    return std::tolower(static_cast<unsigned char>(ch1)) == 
                           std::tolower(static_cast<unsigned char>(ch2));
                }
            );
            return it != content.end();
        }
    } catch (...) {
        // 모든 예외를 잡아 false 반환
        return false;
    }
}