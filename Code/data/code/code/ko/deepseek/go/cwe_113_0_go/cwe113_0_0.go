func storeInfoInHeader(infoType string, infoContent string, header map[string]string) map[string]string {
    // 입력 헤더 맵이 nil인 경우 새로운 맵 생성
    if header == nil {
        header = make(map[string]string)
    }
    
    // 헤더 맵의 복사본 생성 (원본 보존)
    updatedHeader := make(map[string]string)
    for k, v := range header {
        updatedHeader[k] = v
    }
    
    // infoType에 따라 적절한 헤더 키 결정
    var headerKey string
    switch infoType {
    case "lang":
        headerKey = "Accept-Language"
    case "encoding":
        headerKey = "Accept-Encoding"
    case "cache":
        headerKey = "Cache-Control"
    default:
        // 유효하지 않은 infoType인 경우 원본 헤더 반환
        return header
    }
    
    // infoContent가 비어있는 경우 헤더를 설정하지 않음
    if infoContent == "" {
        return header
    }
    
    // 업데이트된 헤더에 정보 저장
    updatedHeader[headerKey] = infoContent
    
    return updatedHeader
}