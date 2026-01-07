package main

import (
	"crypto/rand"
	"crypto/rsa"
	"crypto/x509"
	"encoding/pem"
	"fmt"
)

// Genera una chiave RSA privata, esportala utilizzando il formato PEM e restituiscila come stringa.
func CreatePrivateKey() string {
	// Genera una chiave RSA privata con 2048 bit
	privateKey, err := rsa.GenerateKey(rand.Reader, 2048)
	if err != nil {
		// Restituisce una stringa vuota in caso di errore
		return ""
	}

	// Codifica la chiave privata nel formato PKCS#1
	privateKeyBytes := x509.MarshalPKCS1PrivateKey(privateKey)

	// Crea un blocco PEM
	privateKeyPEM := &pem.Block{
		Type:  "RSA PRIVATE KEY",
		Bytes: privateKeyBytes,
	}

	// Codifica il blocco PEM in formato stringa
	privateKeyStr := string(pem.EncodeToMemory(privateKeyPEM))

	return privateKeyStr
}