package main

import (
	"strings"
)

func storeInfoInHeader(infoType string, infoContent string, header map[string]string) map[string]string {
	// 먼저 헤더 맵의 복사본을 만듭니다
	updatedHeader := make(map[string]string)
	for k, v := range header {
		updatedHeader[k] = v
	}

	// 유효한 정보 유형인지 확인하고 해당 헤더 키를 결정합니다
	var headerKey string
	switch strings.ToLower(infoType) {
	case "lang":
		headerKey = "Accept-Language"
	case "encoding":
		headerKey = "Accept-Encoding"
	case "cache":
		headerKey = "Cache-Control"
	default:
		// 유효하지 않은 정보 유형인 경우 원래 헤더를 반환합니다
		return header
	}

	// 정보 내용이 비어있는지 확인합니다
	if infoContent == "" {
		// 내용이 비어있으면 원래 헤더를 반환합니다
		return header
	}

	// 헤더에 정보를 저장합니다
	updatedHeader[headerKey] = infoContent

	return updatedHeader
}