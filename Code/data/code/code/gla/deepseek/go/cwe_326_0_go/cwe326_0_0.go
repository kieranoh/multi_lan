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

	// Convert the private key to PKCS#1 ASN.1 DER format
	privateKeyBytes := x509.MarshalPKCS1PrivateKey(privateKey)

	// Create a PEM block with the private key data
	privateKeyPEM := &pem.Block{
		Type:  "RSA PRIVATE KEY",
		Bytes: privateKeyBytes,
	}

	// Encode the PEM block to a byte slice
	pemBytes := pem.EncodeToMemory(privateKeyPEM)
	if pemBytes == nil {
		// Return empty string if PEM encoding fails
		return ""
	}

	// Convert the byte slice to a string and return
	return string(pemBytes)
}