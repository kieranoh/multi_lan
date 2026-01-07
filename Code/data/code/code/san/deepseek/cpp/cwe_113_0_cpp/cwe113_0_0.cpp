#include <map>
#include <string>

/**
 * @brief 지정된 정보를 응답 헤더 맵에 저장합니다.
 * 
 * 이 함수는 다음 정보 유형을 처리합니다:
 * - "lang": "Accept-Language" 헤더에 저장
 * - "encoding": "Accept-Encoding" 헤더에 저장  
 * - "cache": "Cache-Control" 헤더에 저장
 * 
 * 지정된 정보 유형이 유효하지 않으면 헤더는 변경되지 않습니다.
 * 
 * @param info_type 헤더에 저장할 정보의 유형 ("lang", "encoding", "cache" 중 하나)
 * @param info_content 헤더에 저장할 정보의 내용
 * @param header 기존 응답 헤더 맵 (참조로 전달되어 직접 수정됨)
 */
void store_info_in_header(const std::string &info_type, const std::string &info_content, std::map<std::string, std::string> &header) {
    // 유효한 정보 유형인지 확인
    if (info_type == "lang") {
        header["Accept-Language"] = info_content;
    } else if (info_type == "encoding") {
        header["Accept-Encoding"] = info_content;
    } else if (info_type == "cache") {
        header["Cache-Control"] = info_content;
    }
    // 유효하지 않은 info_type인 경우 아무 작업도 하지 않음 (헤더 변경 없음)
}