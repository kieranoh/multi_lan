#include <string>
#include <vector>
#include <algorithm>

bool searchPattern(const std::string& pattern, const std::string& content) {
    // 빈 패턴은 항상 발견된 것으로 간주
    if (pattern.empty()) {
        return true;
    }
    
    // 콘텐츠가 패턴보다 짧으면 발견 불가능
    if (content.length() < pattern.length()) {
        return false;
    }
    
    // 단순한 선형 검색 구현
    // 더 효율적인 알고리즘(KMP, Boyer-Moore 등)으로 대체 가능
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