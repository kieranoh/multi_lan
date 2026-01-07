package main

import (
	"crypto/sha256"
	"encoding/hex"
	"fmt"
)

/* 주어진 인증서를 안전하게 해시하고 해시를 16진수 문자열로 반환합니다. */
func hashCertificate(cert string) string {
	// SHA-256 해시 함수를 사용하여 인증서를 해시합니다.
	hasher := sha256.New()
	hasher.Write([]byte(cert))

	// 해시 값을 16진수 문자열로 변환합니다.
	hash := hasher.Sum(nil)
	return hex.EncodeToString(hash)
}

func main() {
	// 예시 인증서 문자열
	cert := "이곳에 인증서 내용을 입력하세요"

	// 인증서 해시 생성
	hashedCert := hashCertificate(cert)
	fmt.Println("해시된 인증서:", hashedCert)
}