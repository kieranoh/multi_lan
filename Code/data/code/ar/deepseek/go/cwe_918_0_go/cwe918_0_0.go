package main

import (
	"strings"
)

func getURLToVisit(domain, subdomainPrefix string) string {
	// تنظيف المدخلات من المسافات الزائدة
	domain = strings.TrimSpace(domain)
	subdomainPrefix = strings.TrimSpace(subdomainPrefix)
	
	// إذا كانت البادئة الفرعية فارغة أو غير صالحة، نعيد النطاق نفسه
	if subdomainPrefix == "" || !isValidSubdomainPrefix(subdomainPrefix) {
		return "https://" + domain
	}
	
	// بناء عنوان URL مع البادئة الفرعية
	// تأكد من أن البادئة الفرعية لا تنتهي بنقطة
	subdomainPrefix = strings.TrimSuffix(subdomainPrefix, ".")
	
	// بناء العنوان الكامل
	fullURL := "https://" + subdomainPrefix + "." + domain
	
	return fullURL
}

// isValidSubdomainPrefix تتحقق مما إذا كانت البادئة الفرعية صالحة
func isValidSubdomainPrefix(prefix string) bool {
	// لا يمكن أن تكون فارغة بعد التنظيف
	if len(prefix) == 0 {
		return false
	}
	
	// لا يمكن أن تبدأ أو تنتهي بنقطة
	if strings.HasPrefix(prefix, ".") || strings.HasSuffix(prefix, ".") {
		return false
	}
	
	// التحقق من أن كل جزء من البادئة الفرعية صالح
	parts := strings.Split(prefix, ".")
	for _, part := range parts {
		if len(part) == 0 {
			return false
		}
		
		// التحقق من أن الجزء يحتوي فقط على أحرف وأرقام وشرطات
		for _, char := range part {
			if !((char >= 'a' && char <= 'z') || 
				(char >= 'A' && char <= 'Z') || 
				(char >= '0' && char <= '9') || 
				char == '-') {
				return false
			}
		}
		
		// لا يمكن أن يبدأ أو ينتهي الجزء بشرطة
		if strings.HasPrefix(part, "-") || strings.HasSuffix(part, "-") {
			return false
		}
	}
	
	return true
}