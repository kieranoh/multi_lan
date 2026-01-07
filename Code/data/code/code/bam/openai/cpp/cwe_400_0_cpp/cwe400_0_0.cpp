#include <string>

bool searchPattern(const std::string& pattern, const std::string& content) {
    // 패턴이 빈 문자열인 경우, 항상 true를 반환
    if (pattern.empty()) {
        return true;
    }
    
    // 콘텐츠에서 패턴을 찾기
    return content.find(pattern) != std::string::npos;
}