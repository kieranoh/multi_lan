package main

import (
	"crypto/rand"
	"crypto/dsa"
	"encoding/pem"
	"math/big"
)

type DSAPrivateKey struct {
	Version int
	P       *big.Int
	Q       *big.Int
	G       *big.Int
	Y       *big.Int
	X       *big.Int
}

// create_private_key_dsa genera una chiave privata DSA, esportala utilizzando il formato PEM e restituiscila come stringa.
func create_private_key_dsa() string {
	// Genera una nuova chiave DSA
	params := new(dsa.Parameters)
	if err := dsa.GenerateParameters(params, rand.Reader, dsa.L2048N224); err != nil {
		return ""
	}
	privateKey := new(dsa.PrivateKey)
	privateKey.PublicKey.Parameters = *params
	if err := dsa.GenerateKey(privateKey, rand.Reader); err != nil {
		return ""
	}

	// Codifica la chiave privata in formato PEM
	privBytes := x509.MarshalPKCS8PrivateKey(privateKey)
	pemBlock := &pem.Block{
		Type:  "PRIVATE KEY",
		Bytes: privBytes,
	}
	var pemData bytes.Buffer
	if err := pem.Encode(&pemData, pemBlock); err != nil {
		return ""
	}

	return pemData.String()
}