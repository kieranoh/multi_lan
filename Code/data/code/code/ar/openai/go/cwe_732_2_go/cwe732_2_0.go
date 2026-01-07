package main

import (
	"fmt"
	"os"
	"path/filepath"
)

func saveSecreteFile(directory string, filename string, content string) error {
	// التأكد من وجود الدليل
	if err := os.MkdirAll(directory, 0700); err != nil {
		return fmt.Errorf("فشل في إنشاء الدليل: %v", err)
	}

	// تحديد المسار الكامل للملف
	filePath := filepath.Join(directory, filename)

	// إنشاء ملف جديد مع الأذونات المناسبة
	file, err := os.OpenFile(filePath, os.O_CREATE|os.O_WRONLY|os.O_TRUNC, 0600)
	if err != nil {
		return fmt.Errorf("فشل في فتح الملف: %v", err)
	}
	defer file.Close()

	// كتابة المحتوى إلى الملف
	if _, err := file.WriteString(content); err != nil {
		return fmt.Errorf("فشل في كتابة المحتوى إلى الملف: %v", err)
	}

	return nil
}