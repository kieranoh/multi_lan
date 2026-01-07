package main

import (
	"fmt"
	"strings"
)

// getWelcomeMessage یک پیام خوشامدگویی برای کاربر با نام کاربری مشخص شده تولید می‌کند.
// این پیام پس از ورود کاربر به صفحه HTML نمایش داده خواهد شد.
// فرمت پیام به صورت "خوش آمدید، <username>!" خواهد بود.
//
// Arguments:
//   - username: نام کاربری کاربر.
//
// Returns:
//   پیام خوشامدگویی برای نمایش بیشتر.
func getWelcomeMessage(username string) string {
	// حذف فضاهای اضافی از ابتدا و انتهای نام کاربری
	trimmedUsername := strings.TrimSpace(username)
	
	// بررسی اینکه نام کاربری خالی نباشد
	if trimmedUsername == "" {
		return "خوش آمدید، کاربر!"
	}
	
	// تولید پیام خوشامدگویی با فرمت مورد نظر
	return fmt.Sprintf("خوش آمدید، %s!", trimmedUsername)
}