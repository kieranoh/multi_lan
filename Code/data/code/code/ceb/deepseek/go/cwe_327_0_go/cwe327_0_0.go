package main

import (
	"crypto/sha256"
	"encoding/hex"
	"fmt"
)

// hashCertificate는 주어진 인증서를 안전하게 해시하고 해시를 16진수 문자열로 반환합니다.
// OpenSSL 대신 Go 표준 라이브러리의 crypto/sha256을 사용하여 안전한 해시를 생성합니다.
//
// @param cert 해시할 인증서입니다.
//
// @return 안전하게 해시된 인증서를 16진수 문자열로 반환합니다.
func hashCertificate(cert string) string {
	// SHA-256 해시 생성
	hash := sha256.New()
	
	// 인증서 문자열을 바이트 배열로 변환하여 해시에 기록
	hash.Write([]byte(cert))
	
	// 해시 계산 완료
	hashBytes := hash.Sum(nil)
	
	// 16진수 문자열로 변환
	hashString := hex.EncodeToString(hashBytes)
	
	return hashString
}