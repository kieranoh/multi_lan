package main

import (
	"strings"
)

// getURLForQuery یک URL برای پرس و جو اطلاعات کاربر بر اساس یک URL API و یک شناسه کاربر تولید می‌کند.
// اگر شناسه کاربر خالی یا نامعتبر باشد، تابع nil را برمی‌گرداند.
func getURLForQuery(apiURL, userID string) *string {
	// بررسی اینکه شناسه کاربر خالی نباشد
	if strings.TrimSpace(userID) == "" {
		return nil
	}

	// حذف اسلش‌های اضافی از انتهای apiURL
	apiURL = strings.TrimRight(apiURL, "/")

	// ساخت URL نهایی
	result := apiURL + "/" + userID

	return &result
}