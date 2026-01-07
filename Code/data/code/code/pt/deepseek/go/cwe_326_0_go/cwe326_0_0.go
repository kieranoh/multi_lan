package main

import (
	"crypto/rand"
	"crypto/rsa"
	"crypto/x509"
	"encoding/pem"
	"fmt"
)

// CreatePrivateKey gera uma chave RSA privada, exporta-a usando o formato PEM e retorna-a como uma string.
func CreatePrivateKey() string {
	// Gera uma chave RSA privada de 2048 bits
	privateKey, err := rsa.GenerateKey(rand.Reader, 2048)
	if err != nil {
		// Em caso de erro, retorna uma string vazia
		return ""
	}

	// Converte a chave privada para o formato DER
	privateKeyDER := x509.MarshalPKCS1PrivateKey(privateKey)

	// Cria um bloco PEM com o tipo "RSA PRIVATE KEY"
	privateKeyBlock := &pem.Block{
		Type:  "RSA PRIVATE KEY",
		Bytes: privateKeyDER,
	}

	// Codifica o bloco PEM para uma string
	privateKeyPEM := string(pem.EncodeToMemory(privateKeyBlock))

	return privateKeyPEM
}