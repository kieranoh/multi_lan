#include <string>
#include <map>
#include <algorithm>

void store_info_in_header(const std::string &info_type, const std::string &info_content, std::map<std::string, std::string> &header) {
    // 유효한 정보 유형 목록
    static const std::string valid_types[] = {"lang", "encoding", "cache"};
    static const int valid_types_count = sizeof(valid_types) / sizeof(valid_types[0]);
    
    // info_type이 유효한지 확인
    bool is_valid_type = false;
    for (int i = 0; i < valid_types_count; ++i) {
        if (info_type == valid_types[i]) {
            is_valid_type = true;
            break;
        }
    }
    
    // 유효하지 않은 타입이면 원래 헤더를 변경하지 않고 반환
    if (!is_valid_type) {
        return;
    }
    
    // info_content가 비어있는지 확인
    if (info_content.empty()) {
        return;
    }
    
    // 정보 유형에 따라 적절한 헤더 키로 저장
    if (info_type == "lang") {
        header["Accept-Language"] = info_content;
    } else if (info_type == "encoding") {
        header["Accept-Encoding"] = info_content;
    } else if (info_type == "cache") {
        header["Cache-Control"] = info_content;
    }
}