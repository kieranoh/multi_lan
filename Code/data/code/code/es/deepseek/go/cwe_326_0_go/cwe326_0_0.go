package main

import (
	"crypto/rand"
	"crypto/rsa"
	"crypto/x509"
	"encoding/pem"
	"fmt"
)

// Genera una clave RSA privada, expórtala utilizando el formato PEM y devuélvela como una cadena.
func CreatePrivateKey() string {
	// Generar una clave RSA privada de 2048 bits
	privateKey, err := rsa.GenerateKey(rand.Reader, 2048)
	if err != nil {
		// Devolver un string vacío en caso de error
		return ""
	}

	// Convertir la clave privada a formato PKCS#1 DER
	privateKeyBytes := x509.MarshalPKCS1PrivateKey(privateKey)

	// Crear un bloque PEM para la clave privada
	privateKeyPEM := &pem.Block{
		Type:  "RSA PRIVATE KEY",
		Bytes: privateKeyBytes,
	}

	// Codificar el bloque PEM a formato string
	privateKeyString := string(pem.EncodeToMemory(privateKeyPEM))

	return privateKeyString
}