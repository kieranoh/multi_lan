package main

import (
	"crypto/rand"
	"crypto/rsa"
	"crypto/x509"
	"encoding/pem"
	"errors"
)

// CreatePrivateKey generates a new RSA private key and returns it as a PEM-encoded string.
// The generated key has a size of 2048 bits. If key generation or encoding fails,
// an empty string is returned.
func CreatePrivateKey() string {
	// Generate a new RSA private key with 2048 bits
	privateKey, err := rsa.GenerateKey(rand.Reader, 2048)
	if err != nil {
		return ""
	}

	// Convert the private key to PKCS#1 DER format
	privateKeyDER := x509.MarshalPKCS1PrivateKey(privateKey)
	if privateKeyDER == nil {
		return ""
	}

	// Create a PEM block with the private key data
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