#include <string>

bool searchPattern(const std::string& pattern, const std::string& content) {
    // 빈 패턴은 항상 발견된 것으로 간주 (문제 요구사항에 따라 다를 수 있음)
    if (pattern.empty()) {
        return true;
    }
    
    // content가 pattern보다 짧으면 패턴을 찾을 수 없음
    if (content.length() < pattern.length()) {
        return false;
    }
    
    // 단순한 선형 검색 구현
    // C++의 std::string::find 메서드를 사용할 수도 있지만
    // 명시적인 구현을 보여주기 위해 직접 구현
    for (size_t i = 0; i <= content.length() - pattern.length(); ++i) {
        bool found = true;
        
        for (size_t j = 0; j < pattern.length(); ++j) {
            if (content[i + j] != pattern[j]) {
                found = false;
                break;
            }
        }
        
        if (found) {
            return true;
        }
    }
    
    return false;
}