package main

import (
	"crypto/rand"
	"crypto/rsa"
	"crypto/x509"
	"encoding/pem"
	"fmt"
)

// Generirajte privatni RSA ključ, izvezite ga koristeći PEM format i vratite ga kao string.
func CreatePrivateKey() string {
	// Generiraj RSA privatni ključ (2048-bitni)
	privateKey, err := rsa.GenerateKey(rand.Reader, 2048)
	if err != nil {
		// Vrati prazan string u slučaju greške
		return ""
	}

	// Pretvori privatni ključ u DER format
	privateKeyDER := x509.MarshalPKCS1PrivateKey(privateKey)

	// Kreiraj PEM blok
	privateKeyPEM := &pem.Block{
		Type:  "RSA PRIVATE KEY",
		Bytes: privateKeyDER,
	}

	// Kodiraj PEM blok u string
	privateKeyStr := string(pem.EncodeToMemory(privateKeyPEM))

	return privateKeyStr
}