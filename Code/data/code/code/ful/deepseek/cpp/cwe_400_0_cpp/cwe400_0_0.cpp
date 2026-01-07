#include <string>
#include <algorithm>
#include <regex>

bool searchPattern(const std::string& pattern, const std::string& content) {
    // 빈 패턴은 항상 발견된 것으로 간주
    if (pattern.empty()) {
        return true;
    }
    
    // 빈 콘텐츠에서는 빈 패턴 외에는 찾을 수 없음
    if (content.empty()) {
        return false;
    }
    
    try {
        // 패턴에 정규식 특수 문자가 있는지 확인
        // 간단한 문자열 검색보다 정규식 검색이 필요할 수 있음
        // 여기서는 기본적으로 문자열 검색을 사용하되,
        // 패턴에 정규식 특수 문자가 있을 경우를 대비해 예외 처리
        
        // 먼저 간단한 문자열 검색 시도
        if (content.find(pattern) != std::string::npos) {
            return true;
        }
        
        // 문자열 검색이 실패하면 정규식 검색 시도
        // 패턴이 유효한 정규식인지 확인하기 위해 try-catch 사용
        std::regex regexPattern;
        try {
            regexPattern = std::regex(pattern);
            if (std::regex_search(content, regexPattern)) {
                return true;
            }
        } catch (const std::regex_error&) {
            // 유효하지 않은 정규식이면 문자열 검색 결과만 사용
            // 이미 문자열 검색에서 false를 반환했으므로 여기서는 아무 작업도 하지 않음
        }
        
        return false;
    } catch (...) {
        // 모든 예외를 잡아 false 반환
        return false;
    }
}