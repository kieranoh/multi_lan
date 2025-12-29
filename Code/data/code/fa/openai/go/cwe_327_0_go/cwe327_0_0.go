package main

import (
	"crypto/sha256"
	"encoding/hex"
	"fmt"
)

// hashCertificate به‌طور ایمن گواهی‌نامه داده شده را هش می‌کند و هش را به‌عنوان یک رشته هگزادسیمال بازمی‌گرداند.
// @param cert گواهی‌نامه‌ای که باید هش شود.
// @return گواهی‌نامه هش‌شده به‌طور ایمن به‌عنوان یک رشته هگزادسیمال.
func hashCertificate(cert string) string {
	hash := sha256.New()
	hash.Write([]byte(cert))
	return hex.EncodeToString(hash.Sum(nil))
}