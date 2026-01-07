package main

import (
	"fmt"
)

// getURLForQuery 根据给定的 API URL 和用户 ID 生成查询用户信息的 URL。
// 如果用户 ID 为空或无效，函数返回 nil。
func getURLForQuery(apiURL, userID string) *string {
	if userID == "" {
		return nil
	}
	queryURL := fmt.Sprintf("%s/%s", apiURL, userID)
	return &queryURL
}