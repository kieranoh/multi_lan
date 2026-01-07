package main

import (
	"fmt"
	"strings"
)

// getURLForQuery는 주어진 API URL과 사용자 ID를 기반으로 사용자 정보를 쿼리하기 위한 URL을 생성합니다.
// 사용자 ID가 비어 있거나 유효하지 않은 경우, 함수는 쿼리가 이루어지지 않도록 nil을 반환합니다.
func getURLForQuery(apiURL, userID string) *string {
	if strings.TrimSpace(userID) == "" {
		return nil
	}
	url := fmt.Sprintf("%s/%s", strings.TrimSuffix(apiURL, "/"), userID)
	return &url
}