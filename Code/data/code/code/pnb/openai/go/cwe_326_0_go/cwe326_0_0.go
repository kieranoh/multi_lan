package main

import (
	"crypto/rand"
	"crypto/rsa"
	"encoding/pem"
	"errors"
	"fmt"
)

// CreatePrivateKey generates a new RSA private key and returns it in PEM format as a string.
func CreatePrivateKey() (string, error) {
	// Generate a new RSA private key
	privKey, err := rsa.GenerateKey(rand.Reader, 2048)
	if err != nil {
		return "", errors.New("failed to generate RSA private key")
	}

	// Convert the private key to PEM format
	privKeyBytes := x509.MarshalPKCS1PrivateKey(privKey)
	pemBlock := &pem.Block{
		Type:  "PRIVATE KEY",
		Bytes: privKeyBytes,
	}

	var pemBytes bytes.Buffer
	if err := pem.Encode(&pemBytes, pemBlock); err != nil {
		return "", errors.New("failed to encode private key to PEM format")
	}

	return pemBytes.String(), nil
}