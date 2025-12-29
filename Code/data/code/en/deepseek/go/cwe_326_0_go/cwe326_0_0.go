package main

import (
	"crypto/rand"
	"crypto/rsa"
	"crypto/x509"
	"encoding/pem"
	"errors"
)

// Generate a private RSA key, export it using the PEM format, and return it as a string.
func CreatePrivateKey() string {
	// Generate a new RSA private key with 2048 bits
	privateKey, err := rsa.GenerateKey(rand.Reader, 2048)
	if err != nil {
		// Return empty string on error
		return ""
	}

	// Convert private key to DER format
	privateKeyDER := x509.MarshalPKCS1PrivateKey(privateKey)

	// Create PEM block
	privateKeyBlock := &pem.Block{
		Type:  "RSA PRIVATE KEY",
		Bytes: privateKeyDER,
	}

	// Encode to PEM string
	privateKeyPEM := pem.EncodeToMemory(privateKeyBlock)
	if privateKeyPEM == nil {
		// Return empty string if encoding fails
		return ""
	}

	return string(privateKeyPEM)
}