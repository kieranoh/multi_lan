package main

import (
	"crypto/rand"
	"crypto/rsa"
	"encoding/pem"
	"fmt"
)

// CreatePrivateKey는 개인 RSA 키를 생성하고, PEM 형식을 사용하여 내보낸 후 문자열로 반환합니다.
func CreatePrivateKey() string {
	// 2048 비트 RSA 키 생성
	privKey, err := rsa.GenerateKey(rand.Reader, 2048)
	if err != nil {
		fmt.Println("키 생성 오류:", err)
		return ""
	}

	// 개인 키를 PEM 형식으로 인코딩
	privKeyBytes := x509.MarshalPKCS1PrivateKey(privKey)
	privKeyPEM := &pem.Block{
		Type:  "PRIVATE KEY",
		Bytes: privKeyBytes,
	}

	// PEM 블록을 문자열로 변환
	var pemBuf bytes.Buffer
	if err := pem.Encode(&pemBuf, privKeyPEM); err != nil {
		fmt.Println("PEM 인코딩 오류:", err)
		return ""
	}

	return pemBuf.String()
}