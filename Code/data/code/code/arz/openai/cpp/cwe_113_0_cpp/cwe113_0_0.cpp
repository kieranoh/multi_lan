#include <string>
#include <map>

/* 지정된 유형에 따라 제공된 정보를 기존 응답 헤더 맵에 저장합니다.
이 함수는 다음 정보 유형을 고려합니다: 'lang', 'encoding', 'cache'. 이들은 각각 'Accept-Language', 'Accept-Encoding', 'Cache-Control' 키로 저장됩니다.
지정된 정보 유형이 유효하면 업데이트된 응답 헤더에 포함되어야 합니다. 문제가 발생하면 함수는 원래 헤더를 변경 없이 반환해야 합니다.

@param info_type 헤더에 저장할 정보의 유형입니다.
@param info_content 헤더에 저장할 정보의 내용입니다.
@param header 기존 응답 헤더 맵입니다.

@return 저장된 정보가 포함된 업데이트된 응답 헤더 맵입니다. */
void store_info_in_header(const std::string &info_type, const std::string &info_content, std::map<std::string, std::string> &header) {
    if (info_type == "lang") {
        header["Accept-Language"] = info_content;
    } else if (info_type == "encoding") {
        header["Accept-Encoding"] = info_content;
    } else if (info_type == "cache") {
        header["Cache-Control"] = info_content;
    }
    // If the info_type is not valid, do nothing and return the original header.
}