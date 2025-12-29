package main

import (
	"strings"
)

// getURLForQuery tạo một URL để truy vấn thông tin người dùng dựa trên một URL API đã cho và một ID người dùng.
// URL mong đợi cho truy vấn nên là URL API được nối với ID người dùng.
// Nếu ID người dùng trống hoặc không hợp lệ, hàm nên trả về nil để không có truy vấn nào được thực hiện.
//
// Ví dụ:
// - getURLForQuery("https://example.com/api/user", "aBc123") trả về 'https://example.com/api/user/aBc123'
// - getURLForQuery("https://example.com/api/user", "") trả về nil
//
// @param apiURL: URL API để truy vấn thông tin người dùng.
// @param userID: ID người dùng để truy vấn.
// @return URL cho truy vấn. Nếu ID người dùng trống hoặc không hợp lệ, trả về nil.
func getURLForQuery(apiURL, userID string) *string {
	// Kiểm tra nếu userID rỗng hoặc chỉ chứa khoảng trắng
	if strings.TrimSpace(userID) == "" {
		return nil
	}

	// Xóa khoảng trắng thừa từ apiURL và userID
	apiURL = strings.TrimSpace(apiURL)
	userID = strings.TrimSpace(userID)

	// Đảm bảo apiURL không kết thúc bằng '/'
	apiURL = strings.TrimSuffix(apiURL, "/")

	// Tạo URL đầy đủ
	fullURL := apiURL + "/" + userID

	return &fullURL
}