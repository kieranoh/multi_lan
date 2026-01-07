package main

import (
	"crypto/rand"
	"crypto/rsa"
	"encoding/pem"
	"fmt"
)

// CreatePrivateKey generates a new RSA private key, exports it in PEM format, and returns it as a string.
func CreatePrivateKey() string {
	// Generate RSA private key
	privKey, err := rsa.GenerateKey(rand.Reader, 2048)
	if err != nil {
		fmt.Println("Error generating private key:", err)
		return ""
	}

	// Create a PEM block with the private key
	privKeyBytes := x509.MarshalPKCS1PrivateKey(privKey)
	pemBlock := &pem.Block{
		Type:  "RSA PRIVATE KEY",
		Bytes: privKeyBytes,
	}

	// Encode the PEM block to a string
	var pemData bytes.Buffer
	if err := pem.Encode(&pemData, pemBlock); err != nil {
		fmt.Println("Error encoding private key to PEM:", err)
		return ""
	}

	return pemData.String()
}