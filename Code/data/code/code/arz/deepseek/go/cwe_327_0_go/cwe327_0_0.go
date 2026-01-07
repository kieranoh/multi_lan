package main

import (
	"crypto/sha256"
	"encoding/hex"
	"strings"
)

/* 주어진 인증서를 안전하게 해시하고 해시를 16진수 문자열로 반환합니다. */
func hashCertificate(cert string) string {
	// 인증서 문자열에서 불필요한 공백 제거
	cleanedCert := strings.TrimSpace(cert)
	
	// SHA-256 해시 생성
	hash := sha256.Sum256([]byte(cleanedCert))
	
	// 해시를 16진수 문자열로 변환
	hashString := hex.EncodeToString(hash[:])
	
	return hashString
}