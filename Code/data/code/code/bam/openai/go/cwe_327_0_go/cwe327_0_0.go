package main

import (
	"crypto/sha256"
	"encoding/hex"
)

// 주어진 인증서를 안전하게 해시하고 해시를 16진수 문자열로 반환합니다.
func hashCertificate(cert string) string {
	hash := sha256.New()
	hash.Write([]byte(cert))
	hashBytes := hash.Sum(nil)
	return hex.EncodeToString(hashBytes)
}