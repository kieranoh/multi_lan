#include <string>

bool searchPattern(const std::string& pattern, const std::string& content) {
    // 패턴의 길이가 0이면 false 반환
    if (pattern.empty()) {
        return false;
    }

    // 콘텐츠에서 패턴을 검색
    return content.find(pattern) != std::string::npos;
}