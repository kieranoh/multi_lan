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
//   - 쿼리용 URL을 가리키는 문자열 포인터입니다. 사용자 ID가 비어 있거나 유효하지 않은 경우 nil을 반환합니다.
func getURLForQuery(apiURL, userID string) *string {
	// 사용자 ID가 비어 있는지 확인
	if strings.TrimSpace(userID) == "" {
		return nil
	}

	// API URL이 비어 있는지 확인 (선택적 검증)
	if strings.TrimSpace(apiURL) == "" {
		return nil
	}

	// URL을 올바르게 구성하기 위해 슬래시로 끝나는지 확인
	baseURL := strings.TrimRight(apiURL, "/")
	userID = strings.Trim(userID, "/")

	// URL 조합
	url := baseURL + "/" + userID

	return &url
}