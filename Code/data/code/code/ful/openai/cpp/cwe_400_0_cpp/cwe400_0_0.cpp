#include <string>

bool searchPattern(const std::string& pattern, const std::string& content) {
    // 패턴이 콘텐츠에서 발견되는지 확인
    return content.find(pattern) != std::string::npos;
}