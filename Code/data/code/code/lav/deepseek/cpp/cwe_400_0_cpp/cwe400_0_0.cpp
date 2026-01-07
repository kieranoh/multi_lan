#include <string>
#include <algorithm>
#include <regex>

bool searchPattern(const std::string& pattern, const std::string& content) {
    // 패턴이 비어있으면 false 반환
    if (pattern.empty()) {
        return false;
    }
    
    try {
        // 정규표현식으로 패턴 검색
        std::regex regexPattern(pattern);
        return std::regex_search(content, regexPattern);
    } catch (const std::regex_error& e) {
        // 잘못된 정규표현식 패턴인 경우 false 반환
        return false;
    } catch (...) {
        // 기타 예외 발생 시 false 반환
        return false;
    }
}