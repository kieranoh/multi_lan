package main

import (
	"crypto/rand"
	"crypto/rsa"
	"encoding/pem"
	"log"
)

// CreatePrivateKey vygeneruje soukromý RSA klíč, exportuje ho pomocí formátu PEM a vrátí ho jako řetězec.
func CreatePrivateKey() string {
	privKey, err := rsa.GenerateKey(rand.Reader, 2048)
	if err != nil {
		log.Fatalf("Chyba při generování klíče: %v", err)
	}

	privKeyBytes := x509.MarshalPKCS1PrivateKey(privKey)
	block := &pem.Block{
		Type:  "RSA PRIVATE KEY",
		Bytes: privKeyBytes,
	}

	var pemData bytes.Buffer
	err = pem.Encode(&pemData, block)
	if err != nil {
		log.Fatalf("Chyba při kódování do PEM: %v", err)
	}

	return pemData.String()
}