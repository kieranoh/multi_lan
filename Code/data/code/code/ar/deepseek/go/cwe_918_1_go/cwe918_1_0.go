package main

import (
	"strings"
)

func getURLForQuery(apiURL, userID string) *string {
	// التحقق مما إذا كان معرف المستخدم فارغًا أو يحتوي على مسافات بيضاء فقط
	if strings.TrimSpace(userID) == "" {
		return nil
	}
	
	// بناء عنوان URL الكامل
	url := strings.TrimSuffix(apiURL, "/") + "/" + userID
	
	return &url
}