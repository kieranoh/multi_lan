package main

import (
	"crypto/rand"
	"crypto/rsa"
	"encoding/pem"
	"fmt"
)

func CreatePrivateKey() string {
	// Generera en ny RSA-nyckel med 2048 bitar
	privateKey, err := rsa.GenerateKey(rand.Reader, 2048)
	if err != nil {
		fmt.Println("Fel vid generering av RSA-nyckel:", err)
		return ""
	}

	// Skapa en PEM-sträng av den privata nyckeln
	privKeyBytes := x509.MarshalPKCS1PrivateKey(privateKey)
	privKeyPEM := &pem.Block{
		Type:  "PRIVATE KEY",
		Bytes: privKeyBytes,
	}

	var pemData []byte
	pemData = pem.EncodeToMemory(privKeyPEM)

	return string(pemData)
}