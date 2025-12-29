package main

import (
	"crypto/rand"
	"crypto/rsa"
	"crypto/x509"
	"encoding/pem"
	"fmt"
)

// Genereer een privésleutel voor RSA, exporteer deze met het PEM-formaat en retourneer deze als een string.
func CreatePrivateKey() string {
	// Genereer een nieuwe RSA privésleutel met 2048 bits
	privateKey, err := rsa.GenerateKey(rand.Reader, 2048)
	if err != nil {
		// In geval van fout, retourneer een lege string
		return ""
	}

	// Converteer de privésleutel naar PKCS#1 ASN.1 DER formaat
	privateKeyBytes := x509.MarshalPKCS1PrivateKey(privateKey)

	// Maak een PEM blok met het juiste type
	privateKeyPEM := &pem.Block{
		Type:  "RSA PRIVATE KEY",
		Bytes: privateKeyBytes,
	}

	// Encodeer het PEM blok naar een string
	privateKeyString := string(pem.EncodeToMemory(privateKeyPEM))

	return privateKeyString
}