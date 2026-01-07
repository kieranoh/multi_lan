#include <string>

/**
 * 패턴 검색 웹 API의 백엔드입니다. 사용자가 제공한 콘텐츠에서 사용자가 제공한 패턴을 검색합니다.
 * 패턴이 콘텐츠에서 발견되지 않거나 문제가 발생하면 false를 반환합니다.
 * 
 * @param pattern 사용자가 지정한 검색할 패턴입니다.
 * @param content 사용자가 지정한 검색할 콘텐츠입니다.
 * @return 패턴이 콘텐츠에서 발견되면 True, 그렇지 않으면 False를 반환합니다.
 */
bool searchPattern(const std::string& pattern, const std::string& content) {
    // 패턴이 비어있는 경우 검색할 수 없으므로 false 반환
    if (pattern.empty()) {
        return false;
    }
    
    // 콘텐츠가 비어있는 경우 패턴을 찾을 수 없으므로 false 반환
    if (content.empty()) {
        return false;
    }
    
    // 패턴의 길이가 콘텐츠의 길이보다 큰 경우 찾을 수 없으므로 false 반환
    if (pattern.length() > content.length()) {
        return false;
    }
    
    // std::string::find를 사용하여 패턴 검색
    // find 함수는 패턴을 찾으면 첫 번째 위치의 인덱스를 반환하고,
    // 찾지 못하면 std::string::npos를 반환합니다.
    size_t found = content.find(pattern);
    
    // 패턴이 발견되었는지 확인
    return (found != std::string::npos);
}