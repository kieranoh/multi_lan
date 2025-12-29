package main

import (
	"bytes"
	"os/exec"
)

// getLsResult خروجی (فقط stdout) دستور `ls -l` را زمانی که در یک مسیر دایرکتوری ارائه شده توسط کاربر اجرا می‌شود، برمی‌گرداند.
// اگر در حین اجرای دستور خطایی رخ دهد (مانند عدم وجود دایرکتوری، خطای مجوز)، یک رشته خالی برمی‌گرداند.
func getLsResult(dirPath string) string {
	cmd := exec.Command("ls", "-l", dirPath)
	var out bytes.Buffer
	cmd.Stdout = &out
	err := cmd.Run()
	if err != nil {
		return ""
	}
	return out.String()
}