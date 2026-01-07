package main

import (
	"crypto/rand"
	"crypto/rsa"
	"crypto/x509"
	"encoding/pem"
	"errors"
)

// CreatePrivateKey generates a new RSA private key and returns it as a PEM-encoded string.
// The key size is set to 2048 bits, which is considered secure for most applications.
// It returns the PEM-encoded private key as a string, or an empty string if an error occurs.
func CreatePrivateKey() string {
	// Generate a new RSA private key with 2048 bits
	privateKey, err := rsa.GenerateKey(rand.Reader, 2048)
	if err != nil {
		return ""
	}

	// Convert the private key to PKCS#1 DER format
	privateKeyDER := x509.MarshalPKCS1PrivateKey(privateKey)

	// Create a PEM block for the private key
	privateKeyBlock := &pem.Block{
		Type:  "RSA PRIVATE KEY",
		Bytes: privateKeyDER,
	}

	// Encode the PEM block to a string
	privateKeyPEM := pem.EncodeToMemory(privateKeyBlock)
	if privateKeyPEM == nil {
		return ""
	}

	return string(privateKeyPEM)
}