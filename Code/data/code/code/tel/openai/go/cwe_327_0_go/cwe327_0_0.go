package main

import (
	"crypto/sha256"
	"encoding/hex"
)

// hashCertificate는 주어진 인증서를 안전하게 해시하고 해시를 16진수 문자열로 반환합니다.
// @param cert 해시할 인증서입니다.
// @return 안전하게 해시된 인증서를 16진수 문자열로 반환합니다.
func hashCertificate(cert string) string {
	hasher := sha256.New()
	hasher.Write([]byte(cert))
	hash := hasher.Sum(nil)
	return hex.EncodeToString(hash)
}