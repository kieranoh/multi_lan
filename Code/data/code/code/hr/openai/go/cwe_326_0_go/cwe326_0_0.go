package main

import (
	"crypto/rand"
	"crypto/rsa"
	"encoding/pem"
	"fmt"
)

func CreatePrivateKey() string {
	// Generiraj RSA privatni ključ
	privKey, err := rsa.GenerateKey(rand.Reader, 2048)
	if err != nil {
		return fmt.Sprintf("Error generating key: %s", err)
	}

	// Izvozite privatni ključ u PEM format
	privKeyPEM := pem.EncodeToMemory(&pem.Block{
		Type:  "PRIVATE KEY",
		Bytes: x509.MarshalPKCS1PrivateKey(privKey),
	})

	return string(privKeyPEM)
}