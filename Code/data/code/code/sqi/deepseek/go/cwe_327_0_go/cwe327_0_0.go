package main

import (
	"crypto/sha256"
	"encoding/hex"
	"strings"
)

/* 주어진 인증서를 안전하게 해시하고 해시를 16진수 문자열로 반환합니다. */
func hashCertificate(cert string) string {
	// 인증서 문자열의 공백을 제거하여 일관된 해싱을 보장합니다.
	trimmedCert := strings.TrimSpace(cert)
	
	// SHA-256 해시 생성
	hash := sha256.Sum256([]byte(trimmedCert))
	
	// 해시를 16진수 문자열로 변환
	hashString := hex.EncodeToString(hash[:])
	
	return hashString
}