#include <string>

bool searchPattern(const std::string& pattern, const std::string& content) {
    // 패턴이 비어있거나 콘텐츠가 비어있는 경우, false를 반환
    if (pattern.empty() || content.empty()) {
        return false;
    }

    // 콘텐츠에서 패턴을 검색
    size_t found = content.find(pattern);
    return found != std::string::npos; // 패턴이 발견되면 true 반환
}