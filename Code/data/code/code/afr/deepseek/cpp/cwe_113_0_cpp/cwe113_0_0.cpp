#include <map>
#include <string>
#include <algorithm>
#include <cctype>

void store_info_in_header(const std::string &info_type, const std::string &info_content, std::map<std::string, std::string> &header) {
    // 유효한 정보 유형과 해당 헤더 키 매핑
    static const std::map<std::string, std::string> valid_types = {
        {"lang", "Accept-Language"},
        {"encoding", "Accept-Encoding"},
        {"cache", "Cache-Control"}
    };
    
    // info_type이 유효한지 확인 (대소문자 구분 없이)
    std::string lower_type = info_type;
    std::transform(lower_type.begin(), lower_type.end(), lower_type.begin(),
                   [](unsigned char c) { return std::tolower(c); });
    
    // 유효한 타입인지 확인
    auto it = valid_types.find(lower_type);
    if (it != valid_types.end()) {
        // info_content가 비어있지 않은지 확인
        if (!info_content.empty()) {
            // 헤더 업데이트
            header[it->second] = info_content;
        }
        // info_content가 비어있으면 헤더를 변경하지 않음 (문제 발생으로 간주)
    }
    // 유효하지 않은 타입이면 헤더를 변경하지 않음 (문제 발생으로 간주)
}