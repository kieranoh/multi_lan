#include <map>
#include <string>
#include <algorithm>
#include <cctype>

void store_info_in_header(const std::string &info_type, const std::string &info_content, std::map<std::string, std::string> &header) {
    // 유효한 정보 유형인지 확인
    std::string lower_type = info_type;
    std::transform(lower_type.begin(), lower_type.end(), lower_type.begin(),
                   [](unsigned char c) { return std::tolower(c); });
    
    // 유효한 정보 유형에 해당하는 헤더 키 매핑
    std::string header_key;
    if (lower_type == "lang") {
        header_key = "Accept-Language";
    } else if (lower_type == "encoding") {
        header_key = "Accept-Encoding";
    } else if (lower_type == "cache") {
        header_key = "Cache-Control";
    } else {
        // 유효하지 않은 정보 유형이면 헤더를 변경하지 않고 반환
        return;
    }
    
    // 정보 내용이 비어있지 않은지 확인
    if (!info_content.empty()) {
        header[header_key] = info_content;
    }
}