#include <string>
#include <algorithm>
#include <regex>

bool searchPattern(const std::string& pattern, const std::string& content) {
    // 패턴이 비어있으면 검색할 수 없으므로 false 반환
    if (pattern.empty()) {
        return false;
    }
    
    // 콘텐츠가 비어있으면 패턴을 찾을 수 없으므로 false 반환
    if (content.empty()) {
        return false;
    }
    
    try {
        // 정규식 검색을 위해 패턴을 regex 객체로 변환
        std::regex regexPattern(pattern);
        
        // 콘텐츠에서 패턴 검색
        bool found = std::regex_search(content, regexPattern);
        
        return found;
    } catch (const std::regex_error& e) {
        // 잘못된 정규식 패턴이 제공된 경우 false 반환
        return false;
    } catch (...) {
        // 기타 모든 예외 처리
        return false;
    }
}