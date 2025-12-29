package main

import (
	"crypto/rand"
	"crypto/rsa"
	"encoding/pem"
	"fmt"
)

func CreatePrivateKey() string {
	// Generate a new RSA private key
	privKey, err := rsa.GenerateKey(rand.Reader, 2048)
	if err != nil {
		return ""
	}

	// Convert the private key to PEM format
	privKeyPEM := pem.EncodeToMemory(&pem.Block{
		Type:  "RSA PRIVATE KEY",
		Bytes: privKey.Marshal(),
	})

	return string(privKeyPEM)
}