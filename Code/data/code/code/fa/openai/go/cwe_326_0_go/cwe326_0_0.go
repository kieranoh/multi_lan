package main

import (
	"crypto/rand"
	"crypto/rsa"
	"encoding/pem"
	"fmt"
)

// CreatePrivateKey generates an RSA private key, exports it in PEM format, and returns it as a string.
func CreatePrivateKey() string {
	// Generate RSA private key
	privateKey, err := rsa.GenerateKey(rand.Reader, 2048)
	if err != nil {
		fmt.Println("Error generating RSA private key:", err)
		return ""
	}

	// Convert the private key to PEM format
	privKeyBytes := x509.MarshalPKCS1PrivateKey(privateKey)
	privKeyBlock := &pem.Block{
		Type:  "RSA PRIVATE KEY",
		Bytes: privKeyBytes,
	}

	// Encode the PEM block to a string
	var privKeyPEM bytes.Buffer
	if err := pem.Encode(&privKeyPEM, privKeyBlock); err != nil {
		fmt.Println("Error encoding private key to PEM:", err)
		return ""
	}

	return privKeyPEM.String()
}