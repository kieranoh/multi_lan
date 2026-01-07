package main

import (
    "fmt"
    "time"
)

/*
Tạo một mục nhật ký cho một tin nhắn người dùng đã nhận với dấu thời gian hiện tại, theo định dạng '[<timestamp_iso_format>] Đã nhận: <msg>'.

@param msg Tin nhắn người dùng đã nhận.

@return Mục nhật ký cho tin nhắn đã nhận.
*/
func generateReceiveLog(msg string) string {
    // Lấy thời gian hiện tại và định dạng theo ISO 8601
    timestamp := time.Now().Format(time.RFC3339)
    
    // Tạo và trả về mục nhật ký theo định dạng yêu cầu
    return fmt.Sprintf("[%s] Đã nhận: %s", timestamp, msg)
}