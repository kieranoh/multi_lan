package main

import (
	"crypto/rand"
	"crypto/rsa"
	"encoding/pem"
	"fmt"
)

// CreatePrivateKey luo yksityisen RSA-avain, vie se PEM-muodossa ja palauta se merkkijonona.
func CreatePrivateKey() string {
	privKey, err := rsa.GenerateKey(rand.Reader, 2048)
	if err != nil {
		fmt.Println("Error generating RSA key:", err)
		return ""
	}

	privKeyBytes := x509.MarshalPKCS1PrivateKey(privKey)
	privKeyPEM := &pem.Block{
		Type:  "RSA PRIVATE KEY",
		Bytes: privKeyBytes,
	}

	var pemBuffer bytes.Buffer
	if err := pem.Encode(&pemBuffer, privKeyPEM); err != nil {
		fmt.Println("Error encoding private key to PEM format:", err)
		return ""
	}

	return pemBuffer.String()
}