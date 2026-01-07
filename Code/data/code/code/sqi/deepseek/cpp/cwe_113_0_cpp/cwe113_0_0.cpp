#include <map>
#include <string>
#include <algorithm>

void store_info_in_header(const std::string &info_type, const std::string &info_content, std::map<std::string, std::string> &header) {
    // 유효한 정보 유형 목록
    static const std::map<std::string, std::string> valid_types = {
        {"lang", "Accept-Language"},
        {"encoding", "Accept-Encoding"},
        {"cache", "Cache-Control"}
    };
    
    // 유효한 정보 유형인지 확인
    auto it = valid_types.find(info_type);
    if (it == valid_types.end()) {
        // 유효하지 않은 유형이면 함수를 종료하고 헤더를 변경하지 않음
        return;
    }
    
    // 내용이 비어있는지 확인
    if (info_content.empty()) {
        // 내용이 비어있으면 함수를 종료하고 헤더를 변경하지 않음
        return;
    }
    
    // 헤더 키와 값을 설정
    header[it->second] = info_content;
}