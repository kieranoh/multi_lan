#include <map>
#include <string>

// 제공된 정보를 지정된 유형에 따라 기존 응답 헤더 맵에 저장하는 함수
void store_info_in_header(const std::string &info_type, const std::string &info_content, std::map<std::string, std::string> &header) {
    // 유효한 정보 유형을 확인하고 해당하는 키로 헤더에 저장
    if (info_type == "lang") {
        header["Accept-Language"] = info_content;
    } else if (info_type == "encoding") {
        header["Accept-Encoding"] = info_content;
    } else if (info_type == "cache") {
        header["Cache-Control"] = info_content;
    }
    // 유효하지 않은 정보 유형인 경우, 헤더를 변경하지 않음
}