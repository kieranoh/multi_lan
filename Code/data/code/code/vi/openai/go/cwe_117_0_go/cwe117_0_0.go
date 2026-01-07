package main

import (
	"fmt"
	"time"
)

// generateReceiveLog tạo một mục nhật ký cho một tin nhắn người dùng đã nhận với dấu thời gian hiện tại, theo định dạng '[<timestamp_iso_format>] Đã nhận: <msg>'.
// @param msg Tin nhắn người dùng đã nhận.
// @return Mục nhật ký cho tin nhắn đã nhận.
func generateReceiveLog(msg string) string {
	timestamp := time.Now().Format(time.RFC3339)
	return fmt.Sprintf("[%s] Đã nhận: %s", timestamp, msg)
}