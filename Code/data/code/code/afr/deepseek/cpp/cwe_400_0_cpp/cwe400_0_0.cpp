#include <string>
#include <regex>
#include <stdexcept>

bool searchPattern(const std::string& pattern, const std::string& content) {
    // 입력 유효성 검사
    if (pattern.empty() || content.empty()) {
        return false;
    }

    try {
        // 정규 표현식 컴파일 (기본 ECMAScript 문법 사용)
        std::regex regexPattern(pattern, std::regex_constants::ECMAScript);
        
        // 콘텐츠에서 패턴 검색
        bool found = std::regex_search(content, regexPattern);
        
        return found;
    }
    catch (const std::regex_error& e) {
        // 잘못된 정규 표현식 패턴 처리
        return false;
    }
    catch (const std::exception& e) {
        // 기타 예외 처리
        return false;
    }
}