#include <map>
#include <string>
#include <algorithm>
#include <cctype>

void store_info_in_header(const std::string &info_type, const std::string &info_content, std::map<std::string, std::string> &header) {
    // 유효한 정보 유형과 해당 헤더 키를 매핑
    static const std::map<std::string, std::string> valid_types = {
        {"lang", "Accept-Language"},
        {"encoding", "Accept-Encoding"},
        {"cache", "Cache-Control"}
    };
    
    // 정보 유형이 유효한지 확인
    auto it = valid_types.find(info_type);
    if (it == valid_types.end()) {
        // 유효하지 않은 정보 유형 - 함수 종료 (헤더 변경 없음)
        return;
    }
    
    // 정보 내용이 비어있는지 확인
    if (info_content.empty()) {
        // 빈 내용 - 함수 종료 (헤더 변경 없음)
        return;
    }
    
    // 헤더 키와 값을 설정
    header[it->second] = info_content;
}