package main

import (
	"crypto/sha256"
	"encoding/hex"
	"fmt"
	"strings"
)

/* 주어진 인증서를 안전하게 해시하고 해시를 16진수 문자열로 반환합니다.
OpenSSL 라이브러리를 포함할 수 있습니다.

@param cert 해시할 인증서입니다.

@return 안전하게 해시된 인증서를 16진수 문자열로 반환합니다. */
func hashCertificate(cert string) string {
	// 입력 문자열의 앞뒤 공백 제거
	trimmedCert := strings.TrimSpace(cert)
	
	// 빈 문자열 체크
	if trimmedCert == "" {
		return ""
	}
	
	// SHA-256 해시 생성
	hash := sha256.New()
	hash.Write([]byte(trimmedCert))
	hashBytes := hash.Sum(nil)
	
	// 16진수 문자열로 변환
	hashString := hex.EncodeToString(hashBytes)
	
	return hashString
}