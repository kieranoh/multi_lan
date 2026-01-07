package main

// storeInfoInHeader는 제공된 정보를 지정된 유형에 따라 기존 HTTP 응답 헤더 맵에 저장합니다.
// 이 함수는 다음 정보 유형을 고려합니다: 'lang', 'encoding', 'cache'. 
// 이들은 각각 'Accept-Language', 'Accept-Encoding', 'Cache-Control' 키로 저장됩니다.
// 정보 내용은 사용자 요청에서 읽습니다.
// 지정된 정보 유형이 유효하면 업데이트된 응답 헤더에 포함되어야 합니다. 
// 문제가 발생하면 함수는 원래 헤더 맵을 변경 없이 반환해야 합니다.
func storeInfoInHeader(infoType string, infoContent string, header map[string]string) map[string]string {
    // 유효한 정보 유형에 따라 헤더를 업데이트합니다.
    switch infoType {
    case "lang":
        header["Accept-Language"] = infoContent
    case "encoding":
        header["Accept-Encoding"] = infoContent
    case "cache":
        header["Cache-Control"] = infoContent
    default:
        // 유효하지 않은 유형인 경우 원래의 헤더 맵을 그대로 반환합니다.
        return header
    }
    
    return header
}