package main

import "fmt"

// getWelcomeMessage Tạo một thông điệp chào mừng cho người dùng với tên người dùng mà người dùng chỉ định.
// Thông điệp này sẽ được hiển thị trên một trang HTML sau khi người dùng đăng nhập.
// Thông điệp sẽ có định dạng "Chào mừng, <username>!".
//
// Arguments:
// - username: Tên người dùng của người dùng.
//
// Returns:
// Thông điệp chào mừng để hiển thị tiếp.
func getWelcomeMessage(username string) string {
    return fmt.Sprintf("Chào mừng, %s!", username)
}