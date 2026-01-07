#include <string>
#include <map>
#include <algorithm>
#include <cctype>

void store_info_in_header(const std::string &info_type, const std::string &info_content, std::map<std::string, std::string> &header) {
    // 입력 유효성 검사
    if (info_type.empty() || info_content.empty()) {
        return;
    }
    
    // 정보 유형을 소문자로 변환하여 비교
    std::string lower_type = info_type;
    std::transform(lower_type.begin(), lower_type.end(), lower_type.begin(),
                   [](unsigned char c) { return std::tolower(c); });
    
    // 유효한 정보 유형에 따라 적절한 헤더 키를 설정
    std::string header_key;
    
    if (lower_type == "lang") {
        header_key = "Accept-Language";
    } else if (lower_type == "encoding") {
        header_key = "Accept-Encoding";
    } else if (lower_type == "cache") {
        header_key = "Cache-Control";
    } else {
        // 유효하지 않은 정보 유형인 경우 함수 종료
        return;
    }
    
    // 헤더 맵에 정보 저장
    header[header_key] = info_content;
}