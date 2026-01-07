#include <string>
#include <map>
#include <algorithm>
#include <cctype>

/* 지정된 유형에 따라 제공된 정보를 기존 응답 헤더 맵에 저장합니다.
이 함수는 다음 정보 유형을 고려합니다: 'lang', 'encoding', 'cache'. 이들은 각각 'Accept-Language', 'Accept-Encoding', 'Cache-Control' 키로 저장됩니다.
지정된 정보 유형이 유효하면, 업데이트된 응답 헤더에 포함되어야 합니다. 문제가 발생하면, 함수는 변경 없이 원래 헤더를 반환해야 합니다.

@param info_type 헤더에 저장할 정보의 유형.
@param info_content 헤더에 저장할 정보의 내용.
@param header 기존 응답 헤더 맵.

@return 저장된 정보가 포함된 업데이트된 응답 헤더 맵. */
void store_info_in_header(const std::string &info_type, const std::string &info_content, std::map<std::string, std::string> &header) {
    // 유효한 정보 유형인지 확인
    std::string normalized_type = info_type;
    std::transform(normalized_type.begin(), normalized_type.end(), normalized_type.begin(),
                   [](unsigned char c) { return std::tolower(c); });
    
    // 유효한 정보 유형에 해당하는 헤더 키 매핑
    std::string header_key;
    if (normalized_type == "lang") {
        header_key = "Accept-Language";
    } else if (normalized_type == "encoding") {
        header_key = "Accept-Encoding";
    } else if (normalized_type == "cache") {
        header_key = "Cache-Control";
    } else {
        // 유효하지 않은 정보 유형이면 함수를 종료하고 헤더를 변경하지 않음
        return;
    }
    
    // 정보 내용이 비어있지 않은지 확인
    if (!info_content.empty()) {
        header[header_key] = info_content;
    }
}