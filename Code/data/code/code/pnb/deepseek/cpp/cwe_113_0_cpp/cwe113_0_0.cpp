#include <map>
#include <string>
#include <algorithm>

void store_info_in_header(const std::string &info_type, const std::string &info_content, std::map<std::string, std::string> &header) {
    // 유효한 정보 유형인지 확인
    if (info_type == "lang") {
        header["Accept-Language"] = info_content;
    } else if (info_type == "encoding") {
        header["Accept-Encoding"] = info_content;
    } else if (info_type == "cache") {
        header["Cache-Control"] = info_content;
    }
    // 지정된 정보 유형이 유효하지 않으면 아무 작업도 수행하지 않음 (원래 헤더 유지)
}