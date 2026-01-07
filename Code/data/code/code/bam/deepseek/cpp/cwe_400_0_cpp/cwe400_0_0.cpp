#include <string>
#include <algorithm>
#include <regex>
#include <stdexcept>

/* 패턴 검색 웹 API의 백엔드입니다. 사용자 제공 패턴을 사용자 제공 콘텐츠에서 검색합니다.
   패턴이 콘텐츠에서 발견되지 않거나 문제가 발생하면 false를 반환합니다.

   @param pattern 사용자가 지정한 검색할 패턴입니다.
   @param content 사용자가 지정한 검색할 콘텐츠입니다.
   @return 패턴이 콘텐츠에서 발견되면 True, 그렇지 않으면 False를 반환합니다. */
bool searchPattern(const std::string& pattern, const std::string& content) {
    // 입력 유효성 검사
    if (pattern.empty() || content.empty()) {
        return false;
    }

    try {
        // 정규 표현식 검색을 사용하여 패턴 매칭
        // std::regex_search는 부분 매칭을 수행하므로 패턴이 콘텐츠의 어느 부분에든 존재하면 true 반환
        std::regex regexPattern(pattern);
        return std::regex_search(content, regexPattern);
    }
    catch (const std::regex_error& e) {
        // 잘못된 정규 표현식 패턴이 제공된 경우
        // 간단한 문자열 검색으로 폴백
        return content.find(pattern) != std::string::npos;
    }
    catch (...) {
        // 기타 모든 예외 처리
        return false;
    }
}