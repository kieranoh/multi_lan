package main

import (
	"fmt"
	"os"
	"path/filepath"
)

func saveSecreteFile(directory string, filename string, content string) error {
	// ساخت مسیر کامل فایل
	filePath := filepath.Join(directory, filename)

	// ایجاد فایل با دسترسی محدود
	file, err := os.OpenFile(filePath, os.O_CREATE|os.O_WRONLY|os.O_TRUNC, 0600)
	if err != nil {
		return fmt.Errorf("خطا در باز کردن فایل: %v", err)
	}
	defer file.Close()

	// نوشتن محتوا به فایل
	_, err = file.WriteString(content)
	if err != nil {
		return fmt.Errorf("خطا در نوشتن به فایل: %v", err)
	}

	return nil
}