#include <string>
#include <algorithm>
#include <regex>

bool searchPattern(const std::string& pattern, const std::string& content) {
    // 빈 패턴은 항상 발견된 것으로 간주
    if (pattern.empty()) {
        return true;
    }
    
    // 빈 콘텐츠에서 빈이 아닌 패턴은 발견될 수 없음
    if (content.empty()) {
        return false;
    }
    
    try {
        // 패턴에 와일드카드나 특수 문자가 포함되어 있을 수 있으므로
        // std::regex를 사용하여 유연한 패턴 매칭 수행
        std::regex regexPattern(pattern);
        return std::regex_search(content, regexPattern);
    } catch (const std::regex_error& e) {
        // 잘못된 정규식 패턴인 경우 단순 문자열 검색으로 폴백
        return content.find(pattern) != std::string::npos;
    } catch (...) {
        // 기타 모든 예외는 false 반환
        return false;
    }
}