package main

import (
	"crypto/rsa"
	"crypto/x509"
	"encoding/pem"
	"log"
)

// CreatePrivateKey generates a private RSA key, exports it in PEM format, and returns it as a string.
func CreatePrivateKey() string {
	privateKey, err := rsa.GenerateKey(rand.Reader, 2048)
	if err != nil {
		log.Fatalf("Error generating RSA key: %v", err)
	}

	privASN1 := x509.MarshalPKCS1PrivateKey(privateKey)
	pemBlock := &pem.Block{
		Type:  "RSA PRIVATE KEY",
		Bytes: privASN1,
	}

	var pemData bytes.Buffer
	if err := pem.Encode(&pemData, pemBlock); err != nil {
		log.Fatalf("Error encoding PEM: %v", err)
	}

	return pemData.String()
}