#include <string>
#include <algorithm>
#include <regex>
#include <stdexcept>

bool searchPattern(const std::string& pattern, const std::string& content) {
    // 입력 유효성 검사
    if (pattern.empty() || content.empty()) {
        return false;
    }

    try {
        // 패턴이 정규 표현식으로 해석될 수 있는지 확인
        // 단순 문자열 검색을 위해 std::regex를 사용
        std::regex regexPattern(pattern, std::regex_constants::ECMAScript | std::regex_constants::icase);
        
        // 콘텐츠에서 패턴 검색
        return std::regex_search(content, regexPattern);
    }
    catch (const std::regex_error& e) {
        // 정규 표현식 오류 발생 시 단순 문자열 검색으로 폴백
        // std::regex_error는 유효하지 않은 정규 표현식 패턴 시 발생
        try {
            // 대소문자 구분 없이 검색하기 위해 변환
            std::string lowerContent = content;
            std::string lowerPattern = pattern;
            
            std::transform(lowerContent.begin(), lowerContent.end(), lowerContent.begin(),
                          [](unsigned char c) { return std::tolower(c); });
            std::transform(lowerPattern.begin(), lowerPattern.end(), lowerPattern.begin(),
                          [](unsigned char c) { return std::tolower(c); });
            
            // 단순 문자열 검색 수행
            return lowerContent.find(lowerPattern) != std::string::npos;
        }
        catch (...) {
            // 모든 예외를 잡아 false 반환
            return false;
        }
    }
    catch (...) {
        // 기타 모든 예외 처리
        return false;
    }
}