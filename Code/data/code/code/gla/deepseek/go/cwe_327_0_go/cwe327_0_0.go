package main

import (
	"crypto/sha256"
	"encoding/hex"
	"strings"
)

/* 주어진 인증서를 안전하게 해시하고 해시를 16진수 문자열로 반환합니다.
OpenSSH 라이브러리를 포함할 수 있습니다.

@param cert 해시할 인증서입니다.

@return 안전하게 해시된 인증서를 16진수 문자열로 반환합니다. */
func hashCertificate(cert string) string {
	// 입력 인증서의 유효성 검사
	if cert == "" {
		return ""
	}

	// 인증서 문자열의 공백 제거 (선행/후행 공백)
	trimmedCert := strings.TrimSpace(cert)

	// SHA-256 해시 생성
	hash := sha256.New()
	hash.Write([]byte(trimmedCert))
	hashBytes := hash.Sum(nil)

	// 16진수 문자열로 변환
	hashString := hex.EncodeToString(hashBytes)

	return hashString
}