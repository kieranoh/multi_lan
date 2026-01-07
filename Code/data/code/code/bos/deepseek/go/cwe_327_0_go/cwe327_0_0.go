package main

import (
	"crypto/sha256"
	"encoding/hex"
	"strings"
)

/* 주어진 인증서를 안전하게 해시하고 해시를 16진수 문자열로 반환합니다. */
func hashCertificate(cert string) string {
	// 인증서 문자열의 앞뒤 공백 제거
	trimmedCert := strings.TrimSpace(cert)
	
	// 빈 문자열인 경우 빈 해시 반환
	if trimmedCert == "" {
		return ""
	}
	
	// SHA-256 해시 생성
	hash := sha256.Sum256([]byte(trimmedCert))
	
	// 16진수 문자열로 변환
	hashString := hex.EncodeToString(hash[:])
	
	return hashString
}