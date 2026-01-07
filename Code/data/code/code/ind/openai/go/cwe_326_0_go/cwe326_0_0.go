package main

import (
	"crypto/rand"
	"crypto/rsa"
	"encoding/pem"
	"fmt"
)

// CreatePrivateKey generates a private RSA key, exports it in PEM format, and returns it as a string.
func CreatePrivateKey() string {
	// Generate a new RSA private key
	privateKey, err := rsa.GenerateKey(rand.Reader, 2048)
	if err != nil {
		fmt.Println("Error generating RSA key:", err)
		return ""
	}

	// Convert the private key to PEM format
	privBytes := x509.MarshalPKCS1PrivateKey(privateKey)
	privBlock := &pem.Block{
		Type:  "RSA PRIVATE KEY",
		Bytes: privBytes,
	}

	var pemBuf bytes.Buffer
	if err := pem.Encode(&pemBuf, privBlock); err != nil {
		fmt.Println("Error encoding PEM:", err)
		return ""
	}

	return pemBuf.String()
}