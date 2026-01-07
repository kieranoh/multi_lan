#include <string>
#include <map>
#include <algorithm>

void store_info_in_header(const std::string &info_type, const std::string &info_content, std::map<std::string, std::string> &header) {
    // 유효한 정보 유형 목록
    const std::string valid_types[] = {"lang", "encoding", "cache"};
    
    // info_type이 유효한지 확인
    bool is_valid = false;
    for (const auto &valid_type : valid_types) {
        if (info_type == valid_type) {
            is_valid = true;
            break;
        }
    }
    
    // 유효하지 않은 정보 유형이면 원래 헤더를 변경 없이 반환
    if (!is_valid) {
        return;
    }
    
    // info_content가 비어있는지 확인
    if (info_content.empty()) {
        return;
    }
    
    // 정보 유형에 따라 적절한 헤더 키에 저장
    if (info_type == "lang") {
        header["Accept-Language"] = info_content;
    } else if (info_type == "encoding") {
        header["Accept-Encoding"] = info_content;
    } else if (info_type == "cache") {
        header["Cache-Control"] = info_content;
    }
}