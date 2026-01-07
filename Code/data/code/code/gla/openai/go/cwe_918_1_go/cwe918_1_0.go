package main

import (
	"fmt"
	"strings"
)

// getURLForQuery 사용자 정보를 쿼리하기 위한 URL을 생성합니다.
func getURLForQuery(apiURL, userID string) *string {
	if strings.TrimSpace(userID) == "" {
		return nil
	}
	fullURL := fmt.Sprintf("%s/%s", strings.TrimRight(apiURL, "/"), userID)
	return &fullURL
}