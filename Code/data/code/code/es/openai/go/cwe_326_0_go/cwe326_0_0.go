package main

import (
	"crypto/rsa"
	"crypto/x509"
	"encoding/pem"
	"log"
)

func CreatePrivateKey() string {
	privKey, err := rsa.GenerateKey(rsa.NewFile(), 2048)
	if err != nil {
		log.Fatalf("Error generating RSA key: %s", err)
	}

	privKeyBytes := x509.MarshalPKCS1PrivateKey(privKey)

	pemBlock := &pem.Block{
		Type:  "RSA PRIVATE KEY",
		Bytes: privKeyBytes,
	}

	var pemData []byte
	pemData = pem.EncodeToMemory(pemBlock)

	return string(pemData)
}