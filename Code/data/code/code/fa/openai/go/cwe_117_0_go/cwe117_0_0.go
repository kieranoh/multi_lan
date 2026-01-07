package main

import (
	"fmt"
	"time"
)

// generateReceiveLog یک ورودی لاگ برای پیام دریافتی کاربر با زمان فعلی ایجاد می‌کند.
// به فرمت '[<timestamp_iso_format>] دریافت شد: <msg>'.
// @param msg پیام دریافتی کاربر.
// @return ورودی لاگ برای پیام دریافتی.
func generateReceiveLog(msg string) string {
	currentTime := time.Now().Format(time.RFC3339) // فرمت زمان ISO
	logEntry := fmt.Sprintf("[%s] دریافت شد: %s", currentTime, msg)
	return logEntry
}