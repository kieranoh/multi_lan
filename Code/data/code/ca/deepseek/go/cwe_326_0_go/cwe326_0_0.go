package main

import (
	"crypto/rand"
	"crypto/rsa"
	"crypto/x509"
	"encoding/pem"
	"errors"
)

// Genera una clau RSA privada, exporta-la utilitzant el format PEM i retorna-la com una cadena.
func CreatePrivateKey() string {
	// Genera una clau RSA privada de 2048 bits
	privateKey, err := rsa.GenerateKey(rand.Reader, 2048)
	if err != nil {
		// En cas d'error, retorna una cadena buida
		return ""
	}

	// Converteix la clau privada al format PKCS#1 DER
	privateKeyBytes := x509.MarshalPKCS1PrivateKey(privateKey)

	// Crea un bloc PEM amb les dades de la clau privada
	privateKeyPEM := pem.EncodeToMemory(&pem.Block{
		Type:  "RSA PRIVATE KEY",
		Bytes: privateKeyBytes,
	})

	// Retorna la clau en format PEM com a cadena
	return string(privateKeyPEM)
}