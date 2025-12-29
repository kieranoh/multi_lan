package main

import (
	"crypto/rand"
	"crypto/rsa"
	"crypto/x509"
	"encoding/pem"
	"errors"
)

// CreatePrivateKey generates a private RSA key and exports it as a PEM-formatted string.
func CreatePrivateKey() string {
	// Generate a new RSA private key with 2048 bits
	privateKey, err := rsa.GenerateKey(rand.Reader, 2048)
	if err != nil {
		// In case of error, return an empty string
		return ""
	}

	// Convert the private key to DER-encoded ASN.1 format
	privateKeyBytes := x509.MarshalPKCS1PrivateKey(privateKey)

	// Create a PEM block for the private key
	privateKeyPEM := &pem.Block{
		Type:  "RSA PRIVATE KEY",
		Bytes: privateKeyBytes,
	}

	// Encode the PEM block to a string
	privateKeyString := string(pem.EncodeToMemory(privateKeyPEM))

	return privateKeyString
}