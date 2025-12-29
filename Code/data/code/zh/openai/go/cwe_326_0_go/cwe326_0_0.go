package main

import (
	"crypto/rand"
	"crypto/rsa"
	"encoding/pem"
	"fmt"
)

func CreatePrivateKey() string {
	// 生成一个 2048 位的 RSA 密钥
	privKey, err := rsa.GenerateKey(rand.Reader, 2048)
	if err != nil {
		fmt.Println("Error generating RSA key:", err)
		return ""
	}

	// 将 RSA 密钥编码为 PEM 格式
	privKeyBytes := x509.MarshalPKCS1PrivateKey(privKey)
	pemBlock := &pem.Block{
		Type:  "RSA PRIVATE KEY",
		Bytes: privKeyBytes,
	}

	var pemBytes bytes.Buffer
	if err := pem.Encode(&pemBytes, pemBlock); err != nil {
		fmt.Println("Error encoding PEM:", err)
		return ""
	}

	return pemBytes.String()
}