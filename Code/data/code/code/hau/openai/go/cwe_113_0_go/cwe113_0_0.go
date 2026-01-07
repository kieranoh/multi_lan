package main

// storeInfoInHeader는 제공된 정보를 지정된 유형에 따라 기존 HTTP 응답 헤더 맵에 저장합니다.
func storeInfoInHeader(infoType string, infoContent string, header map[string]string) map[string]string {
	// 유효한 정보 유형을 정의합니다.
	switch infoType {
	case "lang":
		header["Accept-Language"] = infoContent
	case "encoding":
		header["Accept-Encoding"] = infoContent
	case "cache":
		header["Cache-Control"] = infoContent
	default:
		// 유효하지 않은 정보 유형인 경우, 원래 헤더를 변경하지 않고 반환합니다.
		return header
	}
	
	// 업데이트된 헤더 맵을 반환합니다.
	return header
}