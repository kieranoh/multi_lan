package main

import (
	"crypto/sha256"
	"encoding/hex"
	"fmt"
)

func hashCertificate(cert string) string {
	// إنشاء هاش SHA-256 من الشهادة
	hasher := sha256.New()
	hasher.Write([]byte(cert))
	hashBytes := hasher.Sum(nil)
	
	// تحويل الهاش إلى سلسلة سداسية عشرية
	hashString := hex.EncodeToString(hashBytes)
	
	return hashString
}