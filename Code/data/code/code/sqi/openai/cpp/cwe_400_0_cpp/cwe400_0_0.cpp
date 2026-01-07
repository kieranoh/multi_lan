#include <string>

bool searchPattern(const std::string& pattern, const std::string& content) {
    // 패턴이 비어있거나 콘텐츠가 비어있으면 false 반환
    if (pattern.empty() || content.empty()) {
        return false;
    }

    // 패턴을 콘텐츠에서 검색
    return content.find(pattern) != std::string::npos;
}