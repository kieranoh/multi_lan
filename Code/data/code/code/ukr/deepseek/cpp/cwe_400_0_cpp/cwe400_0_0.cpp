#include <string>
#include <algorithm>
#include <regex>
#include <cctype>
#include <locale>

/**
 * @brief 콘텐츠에서 패턴을 검색합니다.
 * 
 * @param pattern 사용자가 지정한 검색할 패턴입니다.
 * @param content 사용자가 지정한 검색할 콘텐츠입니다.
 * @return 콘텐츠에서 패턴이 발견되면 true, 그렇지 않으면 false입니다.
 */
bool searchPattern(const std::string& pattern, const std::string& content) {
    // 패턴이나 콘텐츠가 비어있는 경우 false 반환
    if (pattern.empty() || content.empty()) {
        return false;
    }
    
    // 패턴이 콘텐츠보다 긴 경우 false 반환
    if (pattern.length() > content.length()) {
        return false;
    }
    
    try {
        // 정규 표현식으로 패턴 검색 (대소문자 구분)
        std::regex regexPattern(pattern);
        return std::regex_search(content, regexPattern);
    }
    catch (const std::regex_error& e) {
        // 정규 표현식 오류 발생 시 단순 문자열 검색으로 폴백
        // 패턴에 특수 정규식 문자가 포함되어 있을 수 있으므로
        // std::string::find를 사용한 단순 검색
        return content.find(pattern) != std::string::npos;
    }
    catch (...) {
        // 기타 모든 예외 처리
        return false;
    }
}