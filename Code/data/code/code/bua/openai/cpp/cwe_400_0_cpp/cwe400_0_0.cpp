#include <string>

bool searchPattern(const std::string& pattern, const std::string& content) {
    // 콘텐츠 내에서 패턴을 찾기
    return content.find(pattern) != std::string::npos;
}