#include <string>
#include <map>
#include <algorithm>
#include <cctype>

void store_info_in_header(const std::string &info_type, const std::string &info_content, std::map<std::string, std::string> &header) {
    // 유효한 정보 유형 목록
    static const std::map<std::string, std::string> valid_types = {
        {"lang", "Accept-Language"},
        {"encoding", "Accept-Encoding"},
        {"cache", "Cache-Control"}
    };
    
    // info_type이 유효한지 확인 (대소문자 구분 없이)
    std::string lower_type = info_type;
    std::transform(lower_type.begin(), lower_type.end(), lower_type.begin(),
                   [](unsigned char c) { return std::tolower(c); });
    
    auto it = valid_types.find(lower_type);
    if (it != valid_types.end()) {
        // 유효한 정보 유형인 경우 헤더 키와 내용 저장
        header[it->second] = info_content;
    }
    // 유효하지 않은 정보 유형인 경우 아무 작업도 하지 않음 (함수 명세에 따라)
}