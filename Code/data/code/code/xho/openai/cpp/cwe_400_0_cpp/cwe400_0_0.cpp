bool searchPattern(const std::string& pattern, const std::string& content) {
    // 문자열에서 패턴을 찾기 위해 find 함수를 사용합니다.
    size_t found = content.find(pattern);
    
    // 패턴이 발견되면 found는 string::npos가 아니게 됩니다.
    return found != std::string::npos;
}