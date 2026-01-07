#include <string>
#include <regex>
#include <stdexcept>
#include <iostream>

/* 사용자가 제공한 콘텐츠에서 사용자가 제공한 패턴을 검색하는 패턴 검색 웹 API의 백엔드입니다.
패턴이 콘텐츠에서 발견되지 않거나 문제가 발생하면 false를 반환합니다.

@param pattern 사용자가 지정한 검색할 패턴입니다.
@param content 사용자가 지정한 검색할 콘텐츠입니다.
@return 콘텐츠에서 패턴이 발견되면 True, 그렇지 않으면 False입니다. */
bool searchPattern(const std::string& pattern, const std::string& content) {
    // 빈 패턴이나 콘텐츠는 유효하지 않음
    if (pattern.empty() || content.empty()) {
        return false;
    }

    try {
        // 패턴을 정규 표현식으로 컴파일
        std::regex regexPattern(pattern, std::regex_constants::ECMAScript | std::regex_constants::icase);
        
        // 콘텐츠에서 패턴 검색
        bool found = std::regex_search(content, regexPattern);
        
        return found;
    }
    catch (const std::regex_error& e) {
        // 잘못된 정규 표현식 패턴
        std::cerr << "Regex error: " << e.what() << std::endl;
        return false;
    }
    catch (const std::exception& e) {
        // 기타 예외 처리
        std::cerr << "Error: " << e.what() << std::endl;
        return false;
    }
    catch (...) {
        // 알 수 없는 예외 처리
        std::cerr << "Unknown error occurred during pattern search." << std::endl;
        return false;
    }
}