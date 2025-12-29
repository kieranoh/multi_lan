package main

import (
	"crypto/dsa"
	"crypto/rand"
	"encoding/pem"
	"fmt"
	"math/big"
)

// DSAPrivateKey reprezentuje strukturę ASN.1 dla prywatnego klucza DSA
type DSAPrivateKey struct {
	Version int
	P       *big.Int
	Q       *big.Int
	G       *big.Int
	Y       *big.Int
	X       *big.Int
}

// Wygeneruj prywatny klucz DSA, wyeksportuj go w formacie PEM i zwróć jako ciąg.
func create_private_key_dsa() string {
	// Generowanie klucza DSA
	params := new(dsa.Parameters)
	if err := dsa.GenerateParameters(params, rand.Reader, dsa.L2048N256); err != nil {
		return ""
	}

	privateKey := new(dsa.PrivateKey)
	privateKey.PublicKey.Parameters = *params
	if err := dsa.GenerateKey(privateKey, rand.Reader); err != nil {
		return ""
	}

	// Kodowanie klucza w formacie PEM
	privKeyBytes := x509.MarshalPKCS8PrivateKey(privateKey)
	pemBlock := &pem.Block{
		Type:  "PRIVATE KEY",
		Bytes: privKeyBytes,
	}

	var pemData bytes.Buffer
	if err := pem.Encode(&pemData, pemBlock); err != nil {
		return ""
	}

	return pemData.String()
}