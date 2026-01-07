#include <string>

bool searchPattern(const std::string& pattern, const std::string& content) {
    // 패턴이 비어 있는 경우 false 반환
    if (pattern.empty()) {
        return false;
    }
    
    // 콘텐츠에서 패턴을 찾기
    return content.find(pattern) != std::string::npos;
}