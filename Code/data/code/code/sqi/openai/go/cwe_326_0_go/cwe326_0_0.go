package main

import (
	"crypto/rand"
	"crypto/rsa"
	"encoding/pem"
	"errors"
	"io/ioutil"
)

func CreatePrivateKey() string {
	// 키 길이를 2048 비트로 설정
	keySize := 2048

	// 새 개인 키 생성
	privKey, err := rsa.GenerateKey(rand.Reader, keySize)
	if err != nil {
		return ""
	}

	// 개인 키를 PEM 형식으로 인코딩
	privKeyBytes := x509.MarshalPKCS1PrivateKey(privKey)
	privKeyPEM := &pem.Block{
		Type:  "PRIVATE KEY",
		Bytes: privKeyBytes,
	}

	// PEM 데이터를 바이트 슬라이스에 저장
	var pemData []byte
	pemData = pem.EncodeToMemory(privKeyPEM)

	return string(pemData)
}