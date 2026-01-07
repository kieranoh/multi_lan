package main

import (
	"strings"
)

func storeInfoInHeader(infoType string, infoContent string, header map[string]string) map[string]string {
	// إنشاء نسخة من الخريطة الأصلية لتجنب تعديلها مباشرة
	updatedHeader := make(map[string]string)
	for k, v := range header {
		updatedHeader[k] = v
	}

	// التحقق من صحة نوع المعلومات
	validTypes := map[string]string{
		"lang":     "Accept-Language",
		"encoding": "Accept-Encoding",
		"cache":    "Cache-Control",
	}

	// البحث عن نوع المعلومات في الخريطة
	headerKey, isValid := validTypes[infoType]
	if !isValid {
		// إذا كان النوع غير صالح، إرجاع الخريطة الأصلية
		return header
	}

	// التحقق من أن محتوى المعلومات ليس فارغًا
	if strings.TrimSpace(infoContent) == "" {
		return header
	}

	// تخزين المعلومات في الرأس
	updatedHeader[headerKey] = infoContent

	return updatedHeader
}