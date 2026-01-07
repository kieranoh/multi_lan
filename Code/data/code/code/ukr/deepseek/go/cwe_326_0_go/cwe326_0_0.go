package main

import (
	"crypto/rand"
	"crypto/rsa"
	"crypto/x509"
	"encoding/pem"
	"errors"
)

// CreatePrivateKey generates an RSA private key and returns it as a PEM-encoded string
func CreatePrivateKey() string {
	// Generate RSA private key with 2048 bits
	privateKey, err := rsa.GenerateKey(rand.Reader, 2048)
	if err != nil {
		// In production, you might want to handle this error differently
		// For this implementation, we'll return an empty string on error
		return ""
	}

	// Convert private key to PKCS#1 ASN.1 DER format
	privateKeyBytes := x509.MarshalPKCS1PrivateKey(privateKey)

	// Create PEM block
	privateKeyPEM := &pem.Block{
		Type:  "RSA PRIVATE KEY",
		Bytes: privateKeyBytes,
	}

	// Encode to PEM format
	pemBytes := pem.EncodeToMemory(privateKeyPEM)
	
	// Convert to string and return
	return string(pemBytes)
}