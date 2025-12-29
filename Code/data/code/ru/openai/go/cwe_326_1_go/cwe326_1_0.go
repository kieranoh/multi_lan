package main

import (
	"crypto/dsa"
	"crypto/rand"
	"crypto/x509"
	"encoding/pem"
	"math/big"
)

// DSAPrivateKey представляет структуру ASN.1 для закрытого ключа DSA
type DSAPrivateKey struct {
	Version int
	P       *big.Int
	Q       *big.Int
	G       *big.Int
	Y       *big.Int
	X       *big.Int
}

// create_private_key_dsa генерирует закрытый ключ DSA, экспортирует его в формате PEM и возвращает его в виде строки.
func create_private_key_dsa() string {
	privateKey := new(dsa.PrivateKey)

	// Генерация ключей DSA
	params := new(dsa.Parameters)
	if err := dsa.GenerateParameters(params, rand.Reader, dsa.L2048N224); err != nil {
		return ""
	}
	if err := privateKey.GenerateKey(params, rand.Reader); err != nil {
		return ""
	}

	// Экспортировать ключ в формате PEM
	privBytes, err := x509.MarshalPKCS8PrivateKey(privateKey)
	if err != nil {
		return ""
	}

	block := &pem.Block{
		Type:  "PRIVATE KEY",
		Bytes: privBytes,
	}

	var pemData []byte
	pemData = pem.EncodeToMemory(block)

	return string(pemData)
}