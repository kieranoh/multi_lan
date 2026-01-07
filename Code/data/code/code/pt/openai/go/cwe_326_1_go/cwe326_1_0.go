package main

import (
	"crypto/dsa"
	"crypto/rand"
	"encoding/pem"
	"math/big"
)

// DSAPrivateKey representa a estrutura ASN.1 para a chave privada DSA
type DSAPrivateKey struct {
	Version int
	P       *big.Int
	Q       *big.Int
	G       *big.Int
	Y       *big.Int
	X       *big.Int
}

// create_private_key_dsa gera uma chave privada DSA, exporta-a usando o formato PEM e retorne-a como uma string.
func create_private_key_dsa() string {
	params := new(dsa.Parameters)
	err := dsa.GenerateParameters(params, rand.Reader, dsa.L2048N256)
	if err != nil {
		return ""
	}

	privateKey := new(dsa.PrivateKey)
	privateKey.PublicKey.Parameters = *params
	err = dsa.GenerateKey(privateKey, rand.Reader)
	if err != nil {
		return ""
	}

	// Convertendo a chave privada DSA para o formato PEM
	privKeyBytes := x509.MarshalPKCS8PrivateKey(privateKey)
	pemBlock := &pem.Block{
		Type:  "PRIVATE KEY",
		Bytes: privKeyBytes,
	}
	pemData := pem.EncodeToMemory(pemBlock)

	return string(pemData)
}