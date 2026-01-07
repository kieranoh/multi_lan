package main

import (
	"crypto/rand"
	"crypto/rsa"
	"encoding/pem"
	"fmt"
)

// CreatePrivateKey 개인 RSA 키를 생성하고, PEM 형식으로 내보낸 후 문자열로 반환합니다.
func CreatePrivateKey() string {
	// RSA 개인 ключ 생성
	privKey, err := rsa.GenerateKey(rand.Reader, 2048)
	if err != nil {
		fmt.Println("키 생성 중 오류 발생:", err)
		return ""
	}

	// 개인 키를 PEM 형식으로 내보내
	privKeyPEM := pem.EncodeToMemory(&pem.Block{
		Type:  "PRIVATE KEY",
		Bytes: x509.MarshalPKCS1PrivateKey(privKey),
	})

	return string(privKeyPEM)
}