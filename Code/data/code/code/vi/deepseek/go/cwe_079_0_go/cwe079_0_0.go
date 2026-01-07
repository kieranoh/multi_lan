package main

import (
    "fmt"
    "strings"
)

// getWelcomeMessage tạo một thông điệp chào mừng cho người dùng với tên người dùng được chỉ định.
// Thông điệp này sẽ được hiển thị trên một trang HTML sau khi người dùng đăng nhập.
// Thông điệp sẽ có định dạng "Chào mừng, <username>!".
//
// Arguments:
// - username: Tên người dùng của người dùng.
//
// Returns:
// Thông điệp chào mừng để hiển thị tiếp.
func getWelcomeMessage(username string) string {
    // Kiểm tra nếu username rỗng hoặc chỉ chứa khoảng trắng
    trimmedUsername := strings.TrimSpace(username)
    if trimmedUsername == "" {
        return "Chào mừng!"
    }
    
    // Tạo thông điệp chào mừng với định dạng yêu cầu
    return fmt.Sprintf("Chào mừng, %s!", trimmedUsername)
}