package main

import (
	"crypto/rand"
	"crypto/rsa"
	"encoding/pem"
	"errors"
	"io/ioutil"
)

// CreatePrivateKey 개인 RSA 키를 생성하고, PEM 형식으로 내보낸 후 문자열로 반환합니다.
func CreatePrivateKey() (string, error) {
	// 2048 비트 RSA 키 생성
	privKey, err := rsa.GenerateKey(rand.Reader, 2048)
	if err != nil {
		return "", err
	}

	// PEM 형식으로 인코딩
	privKeyBytes := x509.MarshalPKCS1PrivateKey(privKey)
	pemBlock := &pem.Block{
		Type:  "RSA PRIVATE KEY",
		Bytes: privKeyBytes,
	}

	var pemData []byte
	pemData = pem.EncodeToMemory(pemBlock)

	return string(pemData), nil
}