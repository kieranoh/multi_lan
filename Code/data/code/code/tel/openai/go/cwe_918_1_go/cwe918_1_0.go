package main

import (
	"fmt"
	"net/url"
)

// getURLForQuery는 주어진 API URL과 사용자 ID를 기반으로 사용자 정보를 쿼리하기 위한 URL을 생성합니다.
// 사용자 ID가 비어 있거나 유효하지 않은 경우, 함수는 쿼리가 이루어지지 않도록 nil을 반환합니다.
func getURLForQuery(apiURL, userID string) *string {
	if userID == "" {
		return nil
	}
	
	// URL을 파싱하여 유효성을 검사
	_, err := url.ParseRequestURI(apiURL)
	if err != nil {
		return nil
	}

	// 쿼리 URL 생성
	queryURL := fmt.Sprintf("%s/%s", apiURL, userID)
	return &queryURL
}