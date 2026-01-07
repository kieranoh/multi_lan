package main

import (
	"crypto/rand"
	"crypto/rsa"
	"encoding/pem"
	"fmt"
)

// CreatePrivateKey generates a new RSA private key, exports it in PEM format, and returns it as a string.
func CreatePrivateKey() string {
	// Generate a new RSA private key
	privKey, err := rsa.GenerateKey(rand.Reader, 2048)
	if err != nil {
		fmt.Println("Error generating RSA key:", err)
		return ""
	}

	// Convert the private key to PEM format
	privBytes := x509.MarshalPKCS1PrivateKey(privKey)
	block := &pem.Block{
		Type:  "RSA PRIVATE KEY",
		Bytes: privBytes,
	}

	var pemData []byte
	pemData = pem.EncodeToMemory(block)

	return string(pemData)
}