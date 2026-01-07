package main

import (
	"strings"
)

// getURLForQuery 根据给定的 API URL 和用户 ID 生成查询用户信息的 URL。
// 预期的查询 URL 应该是 API URL 与用户 ID 的连接。
// 如果用户 ID 为空或无效，函数应返回 nil，以便不进行查询。
//
// 参数:
//   - apiURL: 查询用户信息的 API URL。
//   - userID: 要查询的用户 ID。
//
// 返回:
//   - 查询的 URL。如果用户 ID 为空或无效，返回 nil。
func getURLForQuery(apiURL, userID string) *string {
	// 检查 userID 是否为空或无效（仅包含空白字符）
	if strings.TrimSpace(userID) == "" {
		return nil
	}

	// 确保 apiURL 不以斜杠结尾，userID 不以斜杠开头
	apiURL = strings.TrimSuffix(apiURL, "/")
	userID = strings.TrimPrefix(userID, "/")

	// 构建完整的查询 URL
	queryURL := apiURL + "/" + userID

	return &queryURL
}