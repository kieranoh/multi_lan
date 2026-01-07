package main

import (
	"crypto/rand"
	"crypto/rsa"
	"encoding/pem"
	"fmt"
)

func CreatePrivateKey() string {
	privKey, err := rsa.GenerateKey(rand.Reader, 2048)
	if err != nil {
		panic(err) // 에러 처리
	}

	privKeyPEM := pem.Block{
		Type:  "RSA PRIVATE KEY",
		Bytes: privKey.PrivateKey,
	}

	var pemKey []byte
	pemKey = pem.EncodeToMemory(&privKeyPEM)

	return string(pemKey)
}