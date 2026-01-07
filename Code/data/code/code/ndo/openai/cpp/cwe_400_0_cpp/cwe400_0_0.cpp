#include <string>

bool searchPattern(const std::string& pattern, const std::string& content) {
    // 패턴이 비어 있는 경우 false 반환
    if (pattern.empty()) {
        return false;
    }
    
    // std::string::find를 사용하여 패턴 검색
    return content.find(pattern) != std::string::npos;
}