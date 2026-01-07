#include <string>

bool searchPattern(const std::string& pattern, const std::string& content) {
    // 패턴이 빈 문자열인 경우 무조건 true 반환
    if (pattern.empty()) {
        return true;
    }

    // 콘텐츠에서 패턴을 찾기
    size_t found = content.find(pattern);
    
    // 패턴이 발견되었는지 여부에 따라 true 또는 false 반환
    return (found != std::string::npos);
}