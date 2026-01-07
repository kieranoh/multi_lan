package main

import (
	"crypto/sha256"
	"encoding/hex"
	"fmt"
)

// hashCertificate는 주어진 인증서 문자열을 SHA-256 해시로 변환하고,
// 결과를 16진수 문자열로 반환합니다.
// 이 함수는 인증서 데이터의 무결성을 검증하거나 안전하게 저장하기 위해 사용할 수 있습니다.
//
// 매개변수:
//   - cert: 해시할 인증서 문자열
//
// 반환값:
//   - SHA-256 해시의 16진수 표현 문자열
func hashCertificate(cert string) string {
	// SHA-256 해시 생성
	hasher := sha256.New()
	hasher.Write([]byte(cert))
	hashBytes := hasher.Sum(nil)
	
	// 16진수 문자열로 변환
	hashString := hex.EncodeToString(hashBytes)
	
	return hashString
}