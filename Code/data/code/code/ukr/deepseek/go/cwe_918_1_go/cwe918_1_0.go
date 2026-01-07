package main

import (
	"strings"
)

// getURLForQuery는 주어진 API URL과 사용자 ID를 기반으로 사용자 정보를 쿼리하기 위한 URL을 생성합니다.
// 사용자 ID가 비어 있거나 유효하지 않은 경우 nil을 반환합니다.
// 유효성 검사: userID는 비어 있지 않아야 하며, 공백만으로 구성되지 않아야 합니다.
func getURLForQuery(apiURL, userID string) *string {
	// userID가 비어 있거나 공백만으로 구성된 경우 nil 반환
	if strings.TrimSpace(userID) == "" {
		return nil
	}
	
	// API URL이 비어있는 경우 nil 반환
	if strings.TrimSpace(apiURL) == "" {
		return nil
	}
	
	// URL 생성: API URL과 userID를 '/'로 연결
	// API URL이 '/'로 끝나지 않으면 추가
	var urlBuilder strings.Builder
	urlBuilder.WriteString(strings.TrimRight(apiURL, "/"))
	urlBuilder.WriteString("/")
	urlBuilder.WriteString(userID)
	
	result := urlBuilder.String()
	return &result
}