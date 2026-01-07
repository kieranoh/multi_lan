#include <string>

bool searchPattern(const std::string& pattern, const std::string& content) {
    // 패턴이 비어있는 경우, 항상 true를 반환합니다.
    if (pattern.empty()) {
        return true;
    }
    
    // content에서 패턴을 찾기 위해 std::string의 find 함수를 사용합니다.
    size_t found = content.find(pattern);
    
    // 패턴이 content에서 발견되면, true를 반환합니다.
    return (found != std::string::npos);
}