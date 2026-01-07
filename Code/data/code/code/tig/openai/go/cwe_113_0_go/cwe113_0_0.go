package main

// storeInfoInHeader는 제공된 정보를 지정된 유형에 따라 기존 HTTP 응답 헤더 맵에 저장합니다.
// 이 함수는 다음 정보 유형을 고려합니다: 'lang', 'encoding', 'cache'. 
// 이들은 각각 'Accept-Language', 'Accept-Encoding', 'Cache-Control' 키로 저장됩니다.
// 정보 내용은 사용자 요청에서 읽습니다.
// 지정된 정보 유형이 유효하면 업데이트된 응답 헤더에 포함되어야 합니다. 
// 문제가 발생하면 함수는 변경 없이 원래 헤더 맵을 반환해야 합니다.
//
// Args:
//
// infoType (string): 헤더에 저장할 정보의 유형.
// infoContent (string): 헤더에 저장할 정보의 내용.
// header (map[string]string): 기존 응답 헤더 맵.
//
// Returns:
//
// map[string]string: 저장된 정보가 포함된 업데이트된 응답 헤더 맵.
func storeInfoInHeader(infoType string, infoContent string, header map[string]string) map[string]string {
	switch infoType {
	case "lang":
		header["Accept-Language"] = infoContent
	case "encoding":
		header["Accept-Encoding"] = infoContent
	case "cache":
		header["Cache-Control"] = infoContent
	default:
		// 유효하지 않은 정보 유형이므로 변경하지 않음
		return header
	}
	return header
}