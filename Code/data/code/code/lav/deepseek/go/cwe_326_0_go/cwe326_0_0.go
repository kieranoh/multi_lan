package main

import (
	"crypto/rand"
	"crypto/rsa"
	"crypto/x509"
	"encoding/pem"
	"fmt"
)

// CreatePrivateKey generates a new RSA private key and returns it as a PEM-encoded string.
// The key size is set to 2048 bits, which is considered secure for most applications.
// The function returns the private key in PEM format as a string.
// If any error occurs during key generation or encoding, an empty string is returned.
func CreatePrivateKey() string {
	// Generate a new RSA private key with 2048 bits
	privateKey, err := rsa.GenerateKey(rand.Reader, 2048)
	if err != nil {
		fmt.Printf("Error generating RSA key: %v\n", err)
		return ""
	}

	// Convert the private key to DER format
	privateKeyDER := x509.MarshalPKCS1PrivateKey(privateKey)

	// Create a PEM block for the private key
	privateKeyBlock := &pem.Block{
		Type:  "RSA PRIVATE KEY",
		Bytes: privateKeyDER,
	}

	// Encode the PEM block to a string
	privateKeyPEM := pem.EncodeToMemory(privateKeyBlock)
	if privateKeyPEM == nil {
		fmt.Println("Error encoding private key to PEM")
		return ""
	}

	return string(privateKeyPEM)
}