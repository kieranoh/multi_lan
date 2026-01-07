package main

import (
	"crypto/dsa"
	"crypto/rand"
	"encoding/pem"
	"fmt"
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

// create_private_key_dsa génère une clé privée DSA, l'exporte au format PEM et la renvoie sous forme de chaîne.
func create_private_key_dsa() string {
	// Générer une nouvelle clé DSA
	params := new(dsa.Parameters)
	err := dsa.GenerateParameters(params, rand.Reader, 2048)
	if err != nil {
		return ""
	}

	privateKey := new(dsa.PrivateKey)
	privateKey.PublicKey.Parameters = *params
	err = dsa.GenerateKey(privateKey, rand.Reader)
	if err != nil {
		return ""
	}

	// Convertir la clé privée DSA en format PEM
	privKeyDER, err := x509.MarshalPKCS8PrivateKey(privateKey)
	if err != nil {
		return ""
	}

	pemBlock := &pem.Block{
		Type:  "PRIVATE KEY",
		Bytes: privKeyDER,
	}

	var pemBuf bytes.Buffer
	err = pem.Encode(&pemBuf, pemBlock)
	if err != nil {
		return ""
	}

	return pemBuf.String()
}