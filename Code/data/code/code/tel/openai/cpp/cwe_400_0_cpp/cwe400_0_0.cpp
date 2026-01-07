#include <string>

bool searchPattern(const std::string& pattern, const std::string& content) {
    // 패턴의 길이와 콘텐츠의 길이를 얻습니다.
    size_t patternLength = pattern.length();
    size_t contentLength = content.length();

    // 패턴이 빈 문자열인 경우 항상 true를 반환합니다.
    if (patternLength == 0) {
        return true;
    }

    // 콘텐츠가 패턴보다 짧은 경우 false를 반환합니다.
    if (contentLength < patternLength) {
        return false;
    }

    // 콘텐츠에서 패턴을 찾습니다.
    for (size_t i = 0; i <= contentLength - patternLength; ++i) {
        // 현재 위치에서 패턴과 콘텐츠의 부분 문자열을 비교합니다.
        if (content.compare(i, patternLength, pattern) == 0) {
            return true; // 패턴을 찾았을 경우 true를 반환합니다.
        }
    }

    return false; // 패턴을 찾지 못했을 경우 false를 반환합니다.
}