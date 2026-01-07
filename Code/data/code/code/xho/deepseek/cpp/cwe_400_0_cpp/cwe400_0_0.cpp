#include <string>
#include <algorithm>

bool searchPattern(const std::string& pattern, const std::string& content) {
    // 패턴이 비어있으면 항상 true 반환 (빈 패턴은 모든 콘텐츠에 존재한다고 간주)
    if (pattern.empty()) {
        return true;
    }
    
    // 콘텐츠가 비어있으면 패턴이 비어있지 않은 한 false 반환
    if (content.empty()) {
        return false;
    }
    
    // 패턴 길이가 콘텐츠 길이보다 크면 검색할 수 없음
    if (pattern.length() > content.length()) {
        return false;
    }
    
    // std::string::find를 사용하여 패턴 검색
    // find 함수는 패턴을 찾으면 첫 번째 위치의 인덱스를, 찾지 못하면 std::string::npos를 반환
    size_t found = content.find(pattern);
    
    // 패턴이 발견되었는지 확인
    return (found != std::string::npos);
}