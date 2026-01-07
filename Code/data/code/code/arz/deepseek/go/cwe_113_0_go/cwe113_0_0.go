package main

import (
	"strings"
)

func storeInfoInHeader(infoType string, infoContent string, header map[string]string) map[string]string {
	// 입력 매개변수 유효성 검사
	if infoType == "" || infoContent == "" || header == nil {
		return header
	}

	// 헤더 맵의 복사본 생성 (원본 보존)
	updatedHeader := make(map[string]string)
	for k, v := range header {
		updatedHeader[k] = v
	}

	// 정보 유형에 따른 처리
	switch strings.ToLower(infoType) {
	case "lang":
		// Accept-Language 헤더 설정
		updatedHeader["Accept-Language"] = infoContent
	case "encoding":
		// Accept-Encoding 헤더 설정
		updatedHeader["Accept-Encoding"] = infoContent
	case "cache":
		// Cache-Control 헤더 설정
		updatedHeader["Cache-Control"] = infoContent
	default:
		// 유효하지 않은 정보 유형인 경우 원본 헤더 반환
		return header
	}

	return updatedHeader
}