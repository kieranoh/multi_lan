package main

import (
	"fmt"
	"html"
	"strings"
)

func getWelcomeMessage(username string) string {
	// تنظيف اسم المستخدم لمنع هجمات XSS
	cleanUsername := html.EscapeString(strings.TrimSpace(username))
	
	// إنشاء رسالة الترحيب
	welcomeMessage := fmt.Sprintf("مرحبًا، %s!", cleanUsername)
	
	return welcomeMessage
}