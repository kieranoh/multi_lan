package main

import (
	"strings"
)

// getURLForQuery는 주어진 API URL과 사용자 ID를 기반으로 사용자 정보를 쿼리하기 위한 URL을 생성합니다.
// 사용자 ID가 비어 있거나 유효하지 않은 경우, 함수는 쿼리가 이루어지지 않도록 nil을 반환합니다.
//
// 매개변수:
//   - apiURL: 사용자 정보를 쿼리할 API URL입니다.
//   - userID: 쿼리할 사용자 ID입니다.
//
// 반환값:
//   - 쿼리에 대한 URL 포인터입니다. 사용자 ID가 비어 있거나 유효하지 않은 경우 nil을 반환합니다.
func getURLForQuery(apiURL, userID string) *string {
	// 사용자 ID가 비어있는지 확인
	if strings.TrimSpace(userID) == "" {
		return nil
	}

	// API URL이 비어있는지 확인
	if strings.TrimSpace(apiURL) == "" {
		return nil
	}

	// URL 생성
	// API URL이 슬래시로 끝나지 않으면 추가
	baseURL := strings.TrimRight(apiURL, "/")
	fullURL := baseURL + "/" + userID

	return &fullURL
}