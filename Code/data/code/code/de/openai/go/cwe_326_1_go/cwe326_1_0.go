package main

import (
	"crypto/dsa"
	"crypto/rand"
	"encoding/pem"
	"fmt"
	"math/big"
)

// DSAPrivateKey repräsentiert die ASN.1-Struktur für den DSA-Privatschlüssel
type DSAPrivateKey struct {
	Version int
	P       *big.Int
	Q       *big.Int
	G       *big.Int
	Y       *big.Int
	X       *big.Int
}

// create_private_key_dsa generiert einen privaten DSA-Schlüssel, exportiert ihn im PEM-Format und gibt ihn als String zurück.
func create_private_key_dsa() string {
	params := new(dsa.Parameters)
	if err := dsa.GenerateParameters(params, rand.Reader, dsa.L2048N256); err != nil {
		return ""
	}

	privateKey := new(dsa.PrivateKey)
	privateKey.PublicKey.Parameters = *params
	if err := dsa.GenerateKey(privateKey, rand.Reader); err != nil {
		return ""
	}

	privKeyASN1, err := dsa.MarshalPrivateKey(privateKey)
	if err != nil {
		return ""
	}

	privKeyPEM := &pem.Block{
		Type:  "DSA PRIVATE KEY",
		Bytes: privKeyASN1,
	}

	pemData := pem.EncodeToMemory(privKeyPEM)
	return string(pemData)
}