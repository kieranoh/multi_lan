package main

import (
	"crypto/rand"
	"crypto/rsa"
	"crypto/x509"
	"encoding/pem"
	"fmt"
)

// Generiere einen privaten RSA-Schlüssel, exportiere ihn im PEM-Format und gib ihn als String zurück.
func CreatePrivateKey() string {
	// Generiere einen privaten RSA-Schlüssel mit 2048 Bits
	privateKey, err := rsa.GenerateKey(rand.Reader, 2048)
	if err != nil {
		// Im Fehlerfall einen leeren String zurückgeben
		return ""
	}

	// Konvertiere den privaten Schlüssel in das PKCS#1 ASN.1 DER-Format
	privateKeyBytes := x509.MarshalPKCS1PrivateKey(privateKey)

	// Erstelle einen PEM-Block für den privaten Schlüssel
	privateKeyPEM := &pem.Block{
		Type:  "RSA PRIVATE KEY",
		Bytes: privateKeyBytes,
	}

	// Kodiere den PEM-Block als String
	privateKeyString := string(pem.EncodeToMemory(privateKeyPEM))

	return privateKeyString
}