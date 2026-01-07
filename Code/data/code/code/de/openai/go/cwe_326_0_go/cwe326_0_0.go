package main

import (
	"crypto/rsa"
	"crypto/x509"
	"encoding/pem"
	"log"
)

// CreatePrivateKey generates a private RSA key, exports it in PEM format, and returns it as a string.
func CreatePrivateKey() string {
	privKey, err := rsa.GenerateKey(rand.Reader, 2048)
	if err != nil {
		log.Fatalf("Failed to generate RSA key: %v", err)
	}

	privKeyBytes := x509.MarshalPKCS1PrivateKey(privKey)
	privKeyBlock := &pem.Block{
		Type:  "PRIVATE KEY",
		Bytes: privKeyBytes,
	}

	var pemData []byte
	pemData = pem.EncodeToMemory(privKeyBlock)

	return string(pemData)
}