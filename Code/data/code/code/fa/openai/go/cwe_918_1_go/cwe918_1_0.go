package main

import (
	"fmt"
	"strings"
)

// getURLForQuery تولید یک URL برای پرس و جو اطلاعات کاربر بر اساس یک URL API و یک شناسه کاربر است.
// اگر شناسه کاربر خالی یا نامعتبر باشد، تابع باید nil را برگرداند.
func getURLForQuery(apiURL, userID string) *string {
	if strings.TrimSpace(userID) == "" {
		return nil
	}
	resultURL := fmt.Sprintf("%s/%s", apiURL, userID)
	return &resultURL
}