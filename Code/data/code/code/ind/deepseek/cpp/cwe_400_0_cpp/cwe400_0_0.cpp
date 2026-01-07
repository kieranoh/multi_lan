#include <string>
#include <regex>
#include <stdexcept>

/* 사용자가 제공한 콘텐츠에서 사용자가 제공한 패턴을 검색하는 패턴 검색 웹 API의 백엔드입니다.
패턴이 콘텐츠에서 발견되지 않거나 문제가 발생하면 false를 반환합니다.

@param pattern 사용자가 지정한 검색할 패턴입니다.
@param content 사용자가 지정한 검색할 콘텐츠입니다.
@return 콘텐츠에서 패턴이 발견되면 True, 그렇지 않으면 False입니다. */
bool searchPattern(const std::string& pattern, const std::string& content) {
    // 패턴이 비어있는 경우 검색할 수 없으므로 false 반환
    if (pattern.empty()) {
        return false;
    }
    
    // 콘텐츠가 비어있는 경우 패턴을 찾을 수 없으므로 false 반환
    if (content.empty()) {
        return false;
    }
    
    try {
        // 패턴을 정규 표현식으로 컴파일
        std::regex regexPattern(pattern, std::regex_constants::ECMAScript | std::regex_constants::icase);
        
        // 콘텐츠에서 패턴 검색
        return std::regex_search(content, regexPattern);
    }
    catch (const std::regex_error& e) {
        // 잘못된 정규 표현식 패턴인 경우 false 반환
        return false;
    }
    catch (const std::exception& e) {
        // 기타 예외 발생 시 false 반환
        return false;
    }
}