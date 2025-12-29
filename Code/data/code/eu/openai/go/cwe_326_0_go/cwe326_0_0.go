package main

import (
	"crypto/rand"
	"crypto/rsa"
	"crypto/x509"
	"encoding/pem"
	"fmt"
)

// CreatePrivateKey sortu RSA gako pribatu bat, esportatu PEM formatuan, eta itzuli string gisa.
func CreatePrivateKey() string {
	privateKey, err := rsa.GenerateKey(rand.Reader, 2048)
	if err != nil {
		fmt.Println("Error generating RSA key:", err)
		return ""
	}

	privASN1 := x509.MarshalPKCS1PrivateKey(privateKey)
	privPEM := &pem.Block{
		Type:  "RSA PRIVATE KEY",
		Bytes: privASN1,
	}

	var pemData []byte
	pemData = pem.EncodeToMemory(privPEM)

	return string(pemData)
}