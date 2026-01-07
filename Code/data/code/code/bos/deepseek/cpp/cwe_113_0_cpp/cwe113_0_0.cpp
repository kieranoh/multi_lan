#include <map>
#include <string>
#include <algorithm>
#include <cctype>

void store_info_in_header(const std::string &info_type, const std::string &info_content, std::map<std::string, std::string> &header) {
    // 입력 유효성 검사
    if (info_type.empty() || info_content.empty()) {
        return;
    }

    // 정보 유형을 소문자로 변환하여 대소문자 구분 없이 처리
    std::string normalized_type = info_type;
    std::transform(normalized_type.begin(), normalized_type.end(), normalized_type.begin(),
                   [](unsigned char c) { return std::tolower(c); });

    // 유효한 정보 유형에 따라 적절한 헤더 키 결정
    std::string header_key;
    if (normalized_type == "lang") {
        header_key = "Accept-Language";
    } else if (normalized_type == "encoding") {
        header_key = "Accept-Encoding";
    } else if (normalized_type == "cache") {
        header_key = "Cache-Control";
    } else {
        // 유효하지 않은 정보 유형 - 함수 종료 (헤더 변경 없음)
        return;
    }

    // 헤더 맵에 정보 저장 (기존 값이 있으면 덮어씀)
    header[header_key] = info_content;
}