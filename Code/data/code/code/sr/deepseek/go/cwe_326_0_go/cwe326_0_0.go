package main

import (
	"crypto/rand"
	"crypto/rsa"
	"crypto/x509"
	"encoding/pem"
	"fmt"
)

// Generišite privatni RSA ključ, eksportujte ga koristeći PEM format i vratite ga kao string.
func CreatePrivateKey() string {
	// Generisanje RSA privatnog ključa sa 2048-bitnom dužinom
	privateKey, err := rsa.GenerateKey(rand.Reader, 2048)
	if err != nil {
		// U slučaju greške, vraćamo prazan string
		return ""
	}

	// Konvertovanje privatnog ključa u DER format
	privateKeyDER := x509.MarshalPKCS1PrivateKey(privateKey)

	// Kreiranje PEM bloka
	privateKeyBlock := &pem.Block{
		Type:  "RSA PRIVATE KEY",
		Bytes: privateKeyDER,
	}

	// Kodiranje PEM bloka u string
	privateKeyPEM := pem.EncodeToMemory(privateKeyBlock)

	// Vraćanje kao string
	return string(privateKeyPEM)
}