#include <string>
#include <regex>
#include <stdexcept>

bool searchPattern(const std::string& pattern, const std::string& content) {
    // 입력 유효성 검사
    if (pattern.empty()) {
        // 빈 패턴은 항상 모든 콘텐츠에서 발견된다고 간주
        return true;
    }
    
    if (content.empty()) {
        // 콘텐츠가 비어있으면 패턴을 찾을 수 없음 (패턴이 비어있지 않은 경우)
        return false;
    }
    
    try {
        // 정규 표현식으로 패턴 검색
        // std::regex 기본 생성자는 ECMAScript 문법을 사용
        std::regex regexPattern(pattern);
        
        // 콘텐츠에서 패턴 검색
        return std::regex_search(content, regexPattern);
        
    } catch (const std::regex_error& e) {
        // 잘못된 정규 표현식 패턴인 경우
        // 간단한 문자열 검색으로 폴백
        return content.find(pattern) != std::string::npos;
        
    } catch (const std::exception& e) {
        // 기타 예외 처리
        return false;
    }
}