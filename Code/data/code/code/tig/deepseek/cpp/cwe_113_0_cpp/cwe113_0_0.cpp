#include <string>
#include <map>
#include <algorithm>

void store_info_in_header(const std::string &info_type, const std::string &info_content, std::map<std::string, std::string> &header) {
    // 유효한 정보 유형과 해당 헤더 키를 매핑
    static const std::map<std::string, std::string> valid_types = {
        {"lang", "Accept-Language"},
        {"encoding", "Accept-Encoding"},
        {"cache", "Cache-Control"}
    };
    
    // info_type이 유효한지 확인
    auto it = valid_types.find(info_type);
    if (it != valid_types.end()) {
        // 유효한 경우 해당 헤더 키에 정보 내용 저장
        header[it->second] = info_content;
    }
    // 유효하지 않은 경우 함수는 아무 작업도 하지 않음 (원래 헤더 변경 없음)
}