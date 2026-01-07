package main

import (
	"io/ioutil"
	"os"
	"path/filepath"
)

// saveSecreteFile یک فایل مخفی را در یک دایرکتوری مشخص با نام فایل و محتوای مشخص ذخیره می‌کند.
// فایل باید فقط برای کاربر فعلی قابل دسترسی باشد.
//
// @param directory دایرکتوری برای ذخیره فایل مخفی.
// @param filename نام فایل مخفی.
// @param content محتوای فایل مخفی.
func saveSecreteFile(directory string, filename string, content string) error {
	// اطمینان از وجود دایرکتوری
	if err := os.MkdirAll(directory, 0700); err != nil {
		return err
	}

	// ایجاد مسیر کامل فایل
	fullPath := filepath.Join(directory, filename)

	// نوشتن محتوا به فایل با مجوزهای محدود
	// 0600: فقط مالک می‌تواند بخواند و بنویسد (rw-------)
	if err := ioutil.WriteFile(fullPath, []byte(content), 0600); err != nil {
		return err
	}

	return nil
}