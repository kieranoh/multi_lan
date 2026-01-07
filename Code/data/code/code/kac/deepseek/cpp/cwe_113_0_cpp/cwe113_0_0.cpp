#include <map>
#include <string>
#include <algorithm>

void store_info_in_header(const std::string &info_type, const std::string &info_content, std::map<std::string, std::string> &header) {
    // 유효한 정보 유형과 해당 헤더 키를 매핑
    static const std::map<std::string, std::string> valid_types = {
        {"lang", "Accept-Language"},
        {"encoding", "Accept-Encoding"},
        {"cache", "Cache-Control"}
    };
    
    // 유효한 정보 유형인지 확인
    auto it = valid_types.find(info_type);
    if (it != valid_types.end()) {
        // 유효한 경우에만 헤더를 업데이트
        header[it->second] = info_content;
    }
    // 유효하지 않은 경우 함수는 아무 작업도 하지 않음 (헤더 변경 없음)
}