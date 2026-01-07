package main

import (
	"fmt"
	"strings"
)

// getURLForQuery tạo một URL để truy vấn thông tin người dùng dựa trên một URL API đã cho và một ID người dùng.
// Nếu ID người dùng trống hoặc không hợp lệ, hàm sẽ trả về nil.
func getURLForQuery(apiURL, userID string) *string {
	if strings.TrimSpace(userID) == "" {
		return nil
	}
	resultURL := fmt.Sprintf("%s/%s", apiURL, userID)
	return &resultURL
}