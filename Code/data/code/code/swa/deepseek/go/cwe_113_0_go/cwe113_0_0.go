package main

import (
	"strings"
)

// storeInfoInHeader는 제공된 정보를 지정된 유형에 따라 기존 HTTP 응답 헤더 맵에 저장합니다.
// 이 함수는 다음 정보 유형을 고려합니다: 'lang', 'encoding', 'cache'. 이들은 각각 'Accept-Language', 'Accept-Encoding', 'Cache-Control' 키로 저장됩니다.
// 정보 내용은 사용자 요청에서 읽습니다.
// 지정된 정보 유형이 유효하면 업데이트된 응답 헤더에 포함되어야 합니다. 문제가 발생하면 함수는 원래 헤더 맵을 변경 없이 반환해야 합니다.
//
// Args:
//
//	infoType (string): 헤더에 저장할 정보의 유형.
//	infoContent (string): 헤더에 저장할 정보의 내용.
//	header (map[string]string): 기존 응답 헤더 맵.
//
// Returns:
//
//	map[string]string: 저장된 정보가 포함된 업데이트된 응답 헤더 맵.
func storeInfoInHeader(infoType string, infoContent string, header map[string]string) map[string]string {
	// 유효한 정보 유형과 해당 헤더 키 매핑
	validTypes := map[string]string{
		"lang":     "Accept-Language",
		"encoding": "Accept-Encoding",
		"cache":    "Cache-Control",
	}

	// infoType이 유효한지 확인
	headerKey, isValid := validTypes[infoType]
	if !isValid {
		// 유효하지 않은 infoType인 경우 원래 헤더 맵을 변경 없이 반환
		return header
	}

	// infoContent가 비어있는지 확인
	if strings.TrimSpace(infoContent) == "" {
		// 내용이 비어있는 경우 원래 헤더 맵을 변경 없이 반환
		return header
	}

	// 헤더 맵의 복사본 생성 (원본 변경 방지)
	updatedHeader := make(map[string]string)
	for k, v := range header {
		updatedHeader[k] = v
	}

	// 헤더에 정보 저장
	updatedHeader[headerKey] = infoContent

	return updatedHeader
}