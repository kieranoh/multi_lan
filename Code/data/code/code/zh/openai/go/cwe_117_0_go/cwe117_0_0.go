package main

import (
	"time"
)

// generateReceiveLog 生成一个接收到的用户消息的日志条目，格式为 '[<timestamp_iso_format>] 收到: <msg>'。
//
// @param msg 接收到的用户消息。
// @return 接收到的消息的日志条目。
func generateReceiveLog(msg string) string {
	timestamp := time.Now().Format(time.RFC3339) // 获取当前时间并格式化为 ISO 8601 格式
	logEntry := "[" + timestamp + "] 收到: " + msg // 构建日志条目
	return logEntry // 返回日志条目
}