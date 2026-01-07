#include <map>
#include <string>
#include <algorithm>

void store_info_in_header(const std::string &info_type, const std::string &info_content, std::map<std::string, std::string> &header) {
    // 유효한 정보 유형과 해당 헤더 키를 정의합니다
    const std::map<std::string, std::string> valid_types = {
        {"lang", "Accept-Language"},
        {"encoding", "Accept-Encoding"},
        {"cache", "Cache-Control"}
    };
    
    // 제공된 정보 유형이 유효한지 확인합니다
    auto it = valid_types.find(info_type);
    if (it != valid_types.end()) {
        // 유효한 경우 해당 헤더 키에 정보 내용을 저장합니다
        header[it->second] = info_content;
    }
    // 유효하지 않은 경우 함수는 헤더를 변경하지 않고 반환합니다
}