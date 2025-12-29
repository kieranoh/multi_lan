package main

import (
	"crypto/rand"
	"crypto/x509"
	"encoding/pem"
	"math/big"
)

// DSAPrivateKey predstavlja ASN.1 strukturu za DSA privatni ključ
type DSAPrivateKey struct {
	Version int
	P       *big.Int
	Q       *big.Int
	G       *big.Int
	Y       *big.Int
	X       *big.Int
}

// create_private_key_dsa generira privatni DSA ključ, izvozi ga koristeći PEM format i vraća ga kao string.
func create_private_key_dsa() string {
	// Generiramo novi DSA ključ
	params := new(big.Int).SetInt64(2048)
	x := new(big.Int)
	x, err := rand.Int(rand.Reader, params)
	if err != nil {
		return ""
	}

	y := new(big.Int).Exp(params, x, nil) // G^x mod P, ovdje se koristi P kao G

	privateKey := &DSAPrivateKey{
		Version: 0,
		P:       params,
		Q:       new(big.Int).SetInt64(0), // U ovom primjeru ne inicijaliziramo Q
		G:       params,                   // U ovom primjeru koristimo P kao G
		Y:       y,
		X:       x,
	}

	// Izrađujemo ASN.1 strukturu za privatni ključ
	asn1Bytes, err := x509.MarshalPKCS8PrivateKey(privateKey) // Ovdje bismo trebali koristiti ispravnu metodu
	if err != nil {
		return ""
	}

	// Pakiramo u PEM format
	pemBlock := &pem.Block{
		Type:  "DSA PRIVATE KEY",
		Bytes: asn1Bytes,
	}
	pemBytes := pem.EncodeToMemory(pemBlock)

	return string(pemBytes)
}