package main

import (
	"crypto/rand"
	"crypto/rsa"
	"crypto/x509"
	"encoding/pem"
	"errors"
)

// CreatePrivateKey generates a new RSA private key, exports it in PEM format,
// and returns it as a string.
func CreatePrivateKey() string {
	// Generate a new RSA private key with 2048 bits
	privateKey, err := rsa.GenerateKey(rand.Reader, 2048)
	if err != nil {
		// Return an empty string in case of key generation failure
		return ""
	}

	// Convert the private key to PKCS#1 DER format
	privateKeyDER := x509.MarshalPKCS1PrivateKey(privateKey)

	// Create a PEM block with the private key data
	privateKeyBlock := &pem.Block{
		Type:  "RSA PRIVATE KEY",
		Bytes: privateKeyDER,
	}

	// Encode the PEM block to a byte slice
	privateKeyPEM := pem.EncodeToMemory(privateKeyBlock)

	// Convert the PEM byte slice to a string and return it
	return string(privateKeyPEM)
}