package main

import (
	"crypto/rand"
	"crypto/rsa"
	"encoding/pem"
	"fmt"
)

// CreatePrivateKey generates a private RSA key, exports it in PEM format, and returns it as a string.
func CreatePrivateKey() string {
	// Generate RSA private key
	privateKey, err := rsa.GenerateKey(rand.Reader, 2048)
	if err != nil {
		fmt.Println("Error generating RSA key:", err)
		return ""
	}

	// Create a PEM block with the private key
	privASN1 := privateKey.PrivateKey
	pemBlock := &pem.Block{
		Type:  "PRIVATE KEY",
		Bytes: x509.MarshalPKCS1PrivateKey(privASN1),
	}

	// Convert PEM block to PEM format
	var pemData bytes.Buffer
	if err := pem.Encode(&pemData, pemBlock); err != nil {
		fmt.Println("Error encoding PEM:", err)
		return ""
	}

	return pemData.String()
}