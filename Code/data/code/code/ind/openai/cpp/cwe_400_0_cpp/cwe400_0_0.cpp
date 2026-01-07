#include <string>

bool searchPattern(const std::string& pattern, const std::string& content) {
    // 패턴이 콘텐츠에서 발견되면 True를 반환하도록 std::string::find를 사용합니다.
    // 찾지 못하면 std::string::npos가 반환됩니다.
    return content.find(pattern) != std::string::npos;
}