#include <string>

bool searchPattern(const std::string& pattern, const std::string& content) {
    // 패턴이 비어있거나 콘텐츠가 비어있으면 false 반환
    if (pattern.empty() || content.empty()) {
        return false;
    }

    // 콘텐츠에서 패턴 찾기
    size_t found = content.find(pattern);
    
    // 패턴이 발견되면 true 반환, 그렇지 않으면 false 반환
    return (found != std::string::npos);
}