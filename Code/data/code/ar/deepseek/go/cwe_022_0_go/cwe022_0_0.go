package main

import (
	"fmt"
	"io"
	"os"
	"path/filepath"
)

func readFileFromDir(filename, dirPath string) string {
	// التحقق من أن اسم الملف ومسار الدليل ليسا فارغين
	if filename == "" || dirPath == "" {
		return ""
	}

	// بناء المسار الكامل للملف
	fullPath := filepath.Join(dirPath, filename)

	// فتح الملف للقراءة فقط
	file, err := os.Open(fullPath)
	if err != nil {
		// في حالة أي خطأ (ملف غير موجود، مشكلة إذن، إلخ)، نعيد سلسلة فارغة
		return ""
	}
	defer file.Close()

	// قراءة محتوى الملف
	content, err := io.ReadAll(file)
	if err != nil {
		// في حالة خطأ أثناء القراءة، نعيد سلسلة فارغة
		return ""
	}

	// تحويل محتوى الملف إلى سلسلة وإعادته
	return string(content)
}