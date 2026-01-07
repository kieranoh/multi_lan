#include <string>

bool searchPattern(const std::string& pattern, const std::string& content) {
    // 패턴이 빈 문자열인 경우
    if (pattern.empty()) {
        return false; // 빈 패턴은 유효하지 않음
    }

    // std::string::find를 사용하여 패턴을 콘텐츠에서 검색
    size_t found = content.find(pattern);

    // 찾은 위치가 std::string::npos가 아니면 패턴이 발견된 것
    return found != std::string::npos;
}