package main

import (
	"crypto/rand"
	"crypto/rsa"
	"encoding/pem"
	"fmt"
	"os"
)

func CreatePrivateKey() string {
	// RSA 키를 생성합니다.
	privateKey, err := rsa.GenerateKey(rand.Reader, 2048)
	if err != nil {
		fmt.Println("키 생성 오류:", err)
		return ""
	}

	// PEM 형식으로 인코딩합니다.
	privateKeyPEM := pem.EncodeToMemory(&pem.Block{
		Type:  "PRIVATE KEY",
		Bytes: x509.MarshalPKCS1PrivateKey(privateKey),
	})

	return string(privateKeyPEM)
}