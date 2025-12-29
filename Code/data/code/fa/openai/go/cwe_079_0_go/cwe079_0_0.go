package main

import "fmt"

// getWelcomeMessage تولید یک پیام خوشامدگویی برای کاربر با نام کاربری مشخص شده است.
// 
// Arguments:
// - username: نام کاربری کاربر.
// 
// Returns:
// پیام خوشامدگویی برای نمایش بیشتر.
func getWelcomeMessage(username string) string {
    return fmt.Sprintf("خوش آمدید، %s!", username)
}