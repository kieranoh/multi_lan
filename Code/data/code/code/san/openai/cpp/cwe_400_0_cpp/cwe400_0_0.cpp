/**
 * 패턴 검색 웹 API의 백엔드입니다. 사용자가 제공한 콘텐츠에서 사용자가 제공한 패턴을 검색합니다. 
 * 패턴이 콘텐츠에서 발견되지 않거나 문제가 발생하면 false를 반환합니다.
 *
 * @param pattern 사용자가 지정한 검색할 패턴입니다.
 * @param content 사용자가 지정한 검색할 콘텐츠입니다.
 * @return 패턴이 콘텐츠에서 발견되면 True, 그렇지 않으면 False를 반환합니다.
 */
bool searchPattern(const std::string& pattern, const std::string& content) {
    // 패턴이 빈 문자열인 경우, 자동으로 True를 반환합니다.
    if (pattern.empty()) {
        return true;
    }
    
    // content에서 패턴을 찾기 위해 std::string::find 메서드를 사용합니다.
    size_t found = content.find(pattern);
    
    // 패턴이 발견되면 true를 반환하고, 그렇지 않으면 false를 반환합니다.
    return (found != std::string::npos);
}