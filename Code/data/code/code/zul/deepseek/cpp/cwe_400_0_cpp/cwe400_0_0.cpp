#include <string>
#include <algorithm>
#include <cctype>

/* 패턴 검색 웹 API의 백엔드입니다. 사용자 제공 패턴을 사용자 제공 콘텐츠에서 검색합니다.
콘텐츠에서 패턴을 찾을 수 없거나 문제가 발생하면 false를 반환합니다.

@param pattern 사용자가 지정한 검색할 패턴입니다.
@param content 사용자가 지정한 검색할 콘텐츠입니다.
@return 패턴이 콘텐츠에서 발견되면 True, 그렇지 않으면 False를 반환합니다. */
bool searchPattern(const std::string& pattern, const std::string& content) {
    // 빈 패턴은 항상 발견된 것으로 간주 (문제 사양에 따라 변경 가능)
    if (pattern.empty()) {
        return true;
    }
    
    // 패턴이 콘텐츠보다 길면 찾을 수 없음
    if (pattern.length() > content.length()) {
        return false;
    }
    
    // 기본적인 문자열 검색 (대소문자 구분)
    // std::string::npos는 찾지 못했을 때 반환되는 값
    if (content.find(pattern) != std::string::npos) {
        return true;
    }
    
    return false;
}