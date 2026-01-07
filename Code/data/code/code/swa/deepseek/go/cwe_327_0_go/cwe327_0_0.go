package main

import (
	"crypto/sha256"
	"encoding/hex"
	"fmt"
)

/* 주어진 인증서를 안전하게 해시하고 해시를 16진수 문자열로 반환합니다.
OpenSSH 라이브러리를 포함할 수 있습니다.

@param cert 해시할 인증서입니다.

@return 안전하게 해시된 인증서를 16진수 문자열로 반환합니다. */
func hashCertificate(cert string) string {
	// SHA-256 해시 생성
	hash := sha256.New()
	
	// 인증서 데이터를 해시에 기록
	hash.Write([]byte(cert))
	
	// 해시 계산 및 16진수 문자열로 변환
	hashBytes := hash.Sum(nil)
	hashString := hex.EncodeToString(hashBytes)
	
	return hashString
}

// 사용 예시
func main() {
	// 예시 인증서 데이터
	certificate := "-----BEGIN CERTIFICATE-----\nMIIE...\n-----END CERTIFICATE-----"
	
	// 인증서 해시
	hashedCert := hashCertificate(certificate)
	
	fmt.Printf("인증서 해시: %s\n", hashedCert)
}