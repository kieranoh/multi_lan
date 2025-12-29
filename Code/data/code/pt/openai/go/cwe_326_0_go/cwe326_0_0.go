package main

import (
	"crypto/rand"
	"crypto/rsa"
	"encoding/pem"
	"fmt"
)

// CreatePrivateKey gera uma chave RSA privada, exporta-a usando o formato PEM e retorna-a como uma string.
func CreatePrivateKey() string {
	// Gera uma nova chave RSA de 2048 bits
	privateKey, err := rsa.GenerateKey(rand.Reader, 2048)
	if err != nil {
		fmt.Println("Erro ao gerar chave privada:", err)
		return ""
	}

	// Converte a chave privada para o formato PEM
	privBytes := pem.EncodeToMemory(&pem.Block{
		Type:  "PRIVATE KEY",
		Bytes: x509.MarshalPKCS1PrivateKey(privateKey),
	})

	return string(privBytes)
}