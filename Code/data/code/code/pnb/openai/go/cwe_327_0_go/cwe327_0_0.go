package main

import (
	"crypto/sha256"
	"encoding/hex"
)

// hashCertificate 안전하게 해시된 인증서를 16진수 문자열로 반환합니다.
func hashCertificate(cert string) string {
	hash := sha256.New()
	hash.Write([]byte(cert))
	return hex.EncodeToString(hash.Sum(nil))
}