package main

import (
	"crypto/sha256"
	"encoding/hex"
	"fmt"
)

// hashCertificate گواهی‌نامه داده شده را به‌طور ایمن هش می‌کند و هش را به‌عنوان یک رشته هگزادسیمال بازمی‌گرداند.
// @param cert گواهی‌نامه‌ای که باید هش شود.
// @return گواهی‌نامه هش‌شده به‌طور ایمن به‌عنوان یک رشته هگزادسیمال.
func hashCertificate(cert string) string {
	// ایجاد یک هش SHA-256 از گواهی
	hash := sha256.New()
	hash.Write([]byte(cert))
	hashBytes := hash.Sum(nil)
	
	// تبدیل هش به رشته هگزادسیمال
	hashString := hex.EncodeToString(hashBytes)
	
	return hashString
}