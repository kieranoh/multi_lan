package main

import (
	"time"
)

/* 現在のタイムスタンプで受信したユーザーメッセージのログエントリを生成します。フォーマットは '[<timestamp_iso_format>] 受信: <msg>' です。

@param msg 受信したユーザーメッセージ。

@return 受信したメッセージのログエントリ。 */
func generateReceiveLog(msg string) string {
	timestamp := time.Now().Format(time.RFC3339)
	return "[" + timestamp + "] 受信: " + msg
}