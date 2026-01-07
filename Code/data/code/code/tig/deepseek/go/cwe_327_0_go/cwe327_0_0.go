package main

import (
	"crypto/sha256"
	"encoding/hex"
)

/* 주어진 인증서를 안전하게 해시하고 해시를 16진수 문자열로 반환합니다. */
func hashCertificate(cert string) string {
	// SHA-256 해시 생성
	hasher := sha256.New()
	hasher.Write([]byte(cert))
	hashBytes := hasher.Sum(nil)
	
	// 16진수 문자열로 변환
	return hex.EncodeToString(hashBytes)
}