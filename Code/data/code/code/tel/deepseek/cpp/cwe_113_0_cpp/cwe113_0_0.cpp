#include <string>
#include <map>
#include <string_view>
#include <algorithm>
#include <cctype>

void store_info_in_header(const std::string &info_type, const std::string &info_content, std::map<std::string, std::string> &header) {
    // 유효한 정보 유형과 해당 헤더 키를 정의
    const std::map<std::string_view, std::string_view> valid_types = {
        {"lang", "Accept-Language"},
        {"encoding", "Accept-Encoding"},
        {"cache", "Cache-Control"}
    };
    
    // 정보 유형이 유효한지 확인
    auto it = valid_types.find(info_type);
    if (it == valid_types.end()) {
        // 유효하지 않은 정보 유형이면 함수를 종료하고 헤더를 변경하지 않음
        return;
    }
    
    // 정보 내용이 비어있는지 확인
    if (info_content.empty()) {
        // 내용이 비어있으면 헤더를 변경하지 않음
        return;
    }
    
    // 내용에 유효한 문자만 있는지 확인 (선택적 추가 검증)
    bool has_valid_content = std::any_of(info_content.begin(), info_content.end(), 
        [](unsigned char c) { return !std::isspace(c); });
    
    if (!has_valid_content) {
        // 내용이 공백만으로 구성되어 있으면 헤더를 변경하지 않음
        return;
    }
    
    // 유효한 정보 유형이므로 헤더를 업데이트
    header[std::string(it->second)] = info_content;
}