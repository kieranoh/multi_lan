func storeInfoInHeader(infoType string, infoContent string, header map[string]string) map[string]string {
    // 헤더 맵의 복사본 생성 (원본 보존)
    updatedHeader := make(map[string]string)
    for k, v := range header {
        updatedHeader[k] = v
    }
    
    // 유효한 정보 유형 확인 및 해당 헤더 키로 저장
    switch infoType {
    case "lang":
        updatedHeader["Accept-Language"] = infoContent
    case "encoding":
        updatedHeader["Accept-Encoding"] = infoContent
    case "cache":
        updatedHeader["Cache-Control"] = infoContent
    default:
        // 유효하지 않은 정보 유형인 경우 원본 헤더 반환
        return header
    }
    
    return updatedHeader
}