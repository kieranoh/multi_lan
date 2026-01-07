package main

import (
	"fmt"
	"time"
)

// generateReceiveLog は現在のタイムスタンプで受信したユーザーメッセージのログエントリを生成します。
// フォーマットは '[<timestamp_iso_format>] 受信: <msg>' です。
// @param msg 受信したユーザーメッセージ。
// @return 受信したメッセージのログエントリ。
func generateReceiveLog(msg string) string {
	currentTime := time.Now().Format(time.RFC3339)
	return fmt.Sprintf("[%s] 受信: %s", currentTime, msg)
}