package main

import (
	"crypto/rsa"
	"crypto/x509"
	"encoding/pem"
	"log"
)

// CreatePrivateKey generates a private RSA key and returns it as a PEM encoded string.
func CreatePrivateKey() string {
	privateKey, err := rsa.GenerateKey(rand.Reader, 2048)
	if err != nil {
		log.Fatalf("Error generating RSA key: %v", err)
	}

	privASN1 := x509.MarshalPKCS1PrivateKey(privateKey)
	privBlock := &pem.Block{
		Type:  "RSA PRIVATE KEY",
		Bytes: privASN1,
	}

	privPEM := pem.EncodeToMemory(privBlock)
	return string(privPEM)
}