package main

import (
	"crypto/dsa"
	"crypto/rand"
	"encoding/pem"
	"fmt"
	"math/big"
)

// DSAPrivateKey representerar ASN.1-struktur för DSA privat nyckeltype
type DSAPrivateKey struct {
	Version int
	P       *big.Int
	Q       *big.Int
	G       *big.Int
	Y       *big.Int
	X       *big.Int
}

// create_private_key_dsa genererar en privat DSA-nyckel, exporterar den med PEM-formatet och returnerar den som en sträng.
func create_private_key_dsa() string {
	priv := new(dsa.PrivateKey)
	if err := priv.GenerateParameters(rand.Reader, 2048); err != nil {
		return ""
	}

	if err := priv.GenerateKey(rand.Reader); err != nil {
		return ""
	}

	privBytes, err := x509.MarshalPKCS8PrivateKey(priv)
	if err != nil {
		return ""
	}

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