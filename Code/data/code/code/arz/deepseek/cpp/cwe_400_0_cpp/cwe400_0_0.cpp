#include <string>
#include <vector>
#include <algorithm>

bool searchPattern(const std::string& pattern, const std::string& content) {
    // 빈 패턴은 항상 발견된 것으로 간주 (모든 내용에 빈 문자열이 포함됨)
    if (pattern.empty()) {
        return true;
    }
    
    // 패턴이 콘텐츠보다 길면 발견될 수 없음
    if (pattern.length() > content.length()) {
        return false;
    }
    
    // KMP(Knuth-Morris-Pratt) 알고리즘을 사용한 효율적인 패턴 매칭
    // 부분 일치 테이블(실패 함수) 생성
    std::vector<int> lps(pattern.length(), 0);
    int length = 0;  // 이전까지의 가장 긴 접두사-접미사 길이
    
    for (int i = 1; i < pattern.length(); ) {
        if (pattern[i] == pattern[length]) {
            length++;
            lps[i] = length;
            i++;
        } else {
            if (length != 0) {
                length = lps[length - 1];
            } else {
                lps[i] = 0;
                i++;
            }
        }
    }
    
    // KMP 알고리즘을 사용한 패턴 검색
    int i = 0;  // content 인덱스
    int j = 0;  // pattern 인덱스
    
    while (i < content.length()) {
        if (pattern[j] == content[i]) {
            i++;
            j++;
        }
        
        if (j == pattern.length()) {
            // 패턴 발견
            return true;
        } else if (i < content.length() && pattern[j] != content[i]) {
            if (j != 0) {
                j = lps[j - 1];
            } else {
                i++;
            }
        }
    }
    
    // 패턴을 찾지 못함
    return false;
}