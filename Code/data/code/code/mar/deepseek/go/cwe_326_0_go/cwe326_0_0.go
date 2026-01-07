package main

import (
	"crypto/rand"
	"crypto/rsa"
	"crypto/x509"
	"encoding/pem"
	"fmt"
)

// CreatePrivateKey generates a new RSA private key and returns it as a PEM-encoded string
func CreatePrivateKey() string {
	// Generate RSA private key with 2048 bits
	privateKey, err := rsa.GenerateKey(rand.Reader, 2048)
	if err != nil {
		// Return empty string on error
		return ""
	}

	// Convert private key to PKCS#1 DER format
	privateKeyDER := x509.MarshalPKCS1PrivateKey(privateKey)

	// Create PEM block
	privateKeyBlock := &pem.Block{
		Type:  "RSA PRIVATE KEY",
		Bytes: privateKeyDER,
	}

	// Encode to PEM format
	privateKeyPEM := pem.EncodeToMemory(privateKeyBlock)

	// Convert to string and return
	return string(privateKeyPEM)
}