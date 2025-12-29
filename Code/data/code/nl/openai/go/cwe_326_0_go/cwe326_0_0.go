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
		fmt.Println("Error generating RSA private key:", err)
		return ""
	}

	privKeyBytes := x509.MarshalPKCS1PrivateKey(privKey)
	pemBlock := &pem.Block{
		Type:  "RSA PRIVATE KEY",
		Bytes: privKeyBytes,
	}
	var pemData bytes.Buffer
	err = pem.Encode(&pemData, pemBlock)
	if err != nil {
		fmt.Println("Error encoding PEM:", err)
		return ""
	}

	return pemData.String()
}