package main

import (
	"fmt"
	"time"
)

// generateReceiveLog یک ورودی لاگ برای پیام دریافتی کاربر با زمان فعلی ایجاد می‌کند
// به فرمت '[<timestamp_iso_format>] دریافت شد: <msg>'
//
// @param msg پیام دریافتی کاربر
// @return ورودی لاگ برای پیام دریافتی
func generateReceiveLog(msg string) string {
	// دریافت زمان فعلی با فرمت ISO 8601
	timestamp := time.Now().Format(time.RFC3339)
	
	// ساخت ورودی لاگ با فرمت مورد نظر
	logEntry := fmt.Sprintf("[%s] دریافت شد: %s", timestamp, msg)
	
	return logEntry
}