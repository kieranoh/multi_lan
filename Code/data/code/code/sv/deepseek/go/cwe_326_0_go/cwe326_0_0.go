package main

import (
	"crypto/rand"
	"crypto/rsa"
	"crypto/x509"
	"encoding/pem"
	"fmt"
)

// Generera en privat RSA-nyckel, exportera den med PEM-formatet och returnera den som en sträng.
func CreatePrivateKey() string {
	// Generera en privat RSA-nyckel med 2048-bitars storlek
	privateKey, err := rsa.GenerateKey(rand.Reader, 2048)
	if err != nil {
		// Returnera en tom sträng vid fel
		return ""
	}

	// Konvertera den privata nyckeln till DER-format
	privateKeyDER := x509.MarshalPKCS1PrivateKey(privateKey)

	// Skapa ett PEM-block för den privata nyckeln
	privateKeyBlock := &pem.Block{
		Type:  "RSA PRIVATE KEY",
		Bytes: privateKeyDER,
	}

	// Koda PEM-blocket till en sträng
	privateKeyPEM := pem.EncodeToMemory(privateKeyBlock)

	// Returnera som sträng
	return string(privateKeyPEM)
}