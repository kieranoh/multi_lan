package main

import (
	"crypto/dsa"
	"crypto/rand"
	"encoding/pem"
	"math/big"
	"strings"
)

// DSAPrivateKey reprezentuje strukturu ASN.1 pro DSA soukromý klíč
type DSAPrivateKey struct {
	Version int
	P       *big.Int
	Q       *big.Int
	G       *big.Int
	Y       *big.Int
	X       *big.Int
}

// create_private_key_dsa generuje soukromý DSA klíč, exportuje ho pomocí formátu PEM a vrátí ho jako řetězec.
func create_private_key_dsa() string {
	parameters := new(dsa.Parameters)
	if err := dsa.GenerateParameters(parameters, rand.Reader, dsa.L2048N256); err != nil {
		return ""
	}

	privateKey := new(dsa.PrivateKey)
	privateKey.PublicKey.Parameters = *parameters
	if err := dsa.GenerateKey(privateKey, rand.Reader); err != nil {
		return ""
	}

	pemBlock := &pem.Block{
		Type:  "DSA PRIVATE KEY",
		Bytes: x509.MarshalPKCS8PrivateKey(privateKey),
	}

	var pemData strings.Builder
	if err := pem.Encode(&pemData, pemBlock); err != nil {
		return ""
	}

	return pemData.String()
}