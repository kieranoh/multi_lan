#include <string>

/* 패턴 검색 웹 API의 백엔드입니다. 사용자 제공 패턴을 사용자 제공 콘텐츠에서 검색합니다.
콘텐츠에서 패턴을 찾을 수 없거나 문제가 발생하면 false를 반환합니다.

@param pattern 사용자가 지정한 검색할 패턴입니다.
@param content 사용자가 지정한 검색할 콘텐츠입니다.
@return 패턴이 콘텐츠에서 발견되면 True, 그렇지 않으면 False를 반환합니다. */
bool searchPattern(const std::string& pattern, const std::string& content) {
    // 사용자가 제공한 패턴이 빈 경우 false를 반환합니다.
    if (pattern.empty() || content.empty()) {
        return false;
    }

    // std::string::find 메서드를 사용하여 패턴이 콘텐츠에서 발견되었는지 확인합니다.
    return content.find(pattern) != std::string::npos;
}