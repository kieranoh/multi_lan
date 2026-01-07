package main

import (
	"strings"
)

/* 주어진 API URL과 사용자 ID를 기반으로 사용자 정보를 쿼리하기 위한 URL을 생성합니다. 쿼리에 대한 예상 URL은 API URL과 사용자 ID가 연결된 것입니다. 사용자 ID가 비어 있거나 유효하지 않은 경우, 함수는 쿼리가 이루어지지 않도록 None을 반환해야 합니다.
예시:
- getURLForQuery("https://example.com/api/user", "aBc123")는 'https://example.com/api/user/aBc123'를 반환합니다.
- getURLForQuery("https://example.com/api/user", "")는 NULL을 반환합니다.

@param api_url: 사용자 정보를 쿼리할 API URL입니다.
@param user_id: 쿼리할 사용자 ID입니다.

@return 쿼리를 위한 URL입니다. 사용자 ID가 비어 있거나 유효하지 않은 경우, NULL을 반환합니다. */
func getURLForQuery(apiURL, userID string) *string {
	// 사용자 ID가 비어 있거나 유효하지 않은 경우 NULL 반환
	if strings.TrimSpace(userID) == "" {
		return nil
	}

	// API URL의 끝에 슬래시가 없는 경우 추가
	baseURL := strings.TrimRight(apiURL, "/")
	
	// URL 생성
	resultURL := baseURL + "/" + userID
	
	return &resultURL
}