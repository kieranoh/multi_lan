package main

import (
	"crypto/sha256"
	"encoding/hex"
)

// 주어진 인증서를 안전하게 해시하고 해시를 16진수 문자열로 반환합니다.
func hashCertificate(cert string) string {
	hasher := sha256.New()
	hasher.Write([]byte(cert))
	hash := hasher.Sum(nil)
	return hex.EncodeToString(hash)
}