package main

import (
	"crypto/rand"
	"crypto/rsa"
	"crypto/x509"
	"encoding/pem"
	"fmt"
)

// CreatePrivateKey generates a new RSA private key and returns it as a PEM-encoded string.
// The key size is set to 2048 bits. If any error occurs during key generation or encoding,
// the function returns an empty string.
func CreatePrivateKey() string {
	// Generate a new RSA private key with 2048 bits
	privateKey, err := rsa.GenerateKey(rand.Reader, 2048)
	if err != nil {
		fmt.Printf("Failed to generate RSA private key: %v\n", err)
		return ""
	}

	// Convert the private key to DER-encoded PKCS#1 format
	privateKeyBytes := x509.MarshalPKCS1PrivateKey(privateKey)

	// Create a PEM block for the private key
	privateKeyPEM := &pem.Block{
		Type:  "RSA PRIVATE KEY",
		Bytes: privateKeyBytes,
	}

	// Encode the PEM block to a string
	pemString := string(pem.EncodeToMemory(privateKeyPEM))

	return pemString
}