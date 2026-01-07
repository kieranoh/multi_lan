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
		// Return empty string on key generation failure
		return ""
	}

	// Convert private key to PKCS#1 ASN.1 DER format
	privateKeyBytes := x509.MarshalPKCS1PrivateKey(privateKey)

	// Create PEM block for the private key
	privateKeyPEM := &pem.Block{
		Type:  "RSA PRIVATE KEY",
		Bytes: privateKeyBytes,
	}

	// Encode PEM block to string
	privateKeyStr := string(pem.EncodeToMemory(privateKeyPEM))

	return privateKeyStr
}