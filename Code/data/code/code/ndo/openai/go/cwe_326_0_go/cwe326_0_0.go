package main

import (
	"crypto/rsa"
	"crypto/rand"
	"encoding/pem"
	"errors"
	"io/ioutil"
)

// CreatePrivateKey 생성된 개인 RSA 키를 PEM 형식으로 내보낸 후 문자열로 반환합니다.
func CreatePrivateKey() (string, error) {
	privateKey, err := rsa.GenerateKey(rand.Reader, 2048)
	if err != nil {
		return "", err
	}

	privDER := pem.EncodeToMemory(&pem.Block{
		Type:  "PRIVATE KEY",
		Bytes: x509.MarshalPKCS1PrivateKey(privateKey),
	})

	if privDER == nil {
		return "", errors.New("failed to encode private key to PEM")
	}

	return string(privDER), nil
}