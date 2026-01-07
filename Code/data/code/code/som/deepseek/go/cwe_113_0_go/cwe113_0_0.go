func storeInfoInHeader(infoType string, infoContent string, header map[string]string) map[string]string {
    // 원본 헤더 맵을 변경하지 않도록 복사본 생성
    updatedHeader := make(map[string]string)
    for k, v := range header {
        updatedHeader[k] = v
    }
    
    // 유효한 정보 유형인지 확인하고 해당 헤더 키에 저장
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