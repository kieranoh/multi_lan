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

// createPrivateKeyDSA generiše privatni DSA ključ, eksportuje ga koristeći PEM format i vraća ga kao string.
func createPrivateKeyDSA() string {
	// Generišemo DSA ključ koristeći crypto/rand
	params := new(big.Int).SetInt64(2048)
	dsa := new(big.Int).SetInt64(0)

	// Generisanje privatnog ključa (X)
	x, err := rand.Int(rand.Reader, params)
	if err != nil {
		panic(err)
	}

	// Generisanje javnog ključa (Y) na osnovu X
	y := new(big.Int).Exp(dsa, x, params)

	// Kreiranje DSA privatnog ključa
	privateKey := DSAPrivateKey{
		Version: 0,
		P:       params,
		Q:       dsa, // ovde se koristi dummy vrednost
		G:       dsa, // ovde se koristi dummy vrednost
		Y:       y,
		X:       x,
	}

	// Kodiranje u PEM format
	privKeyBytes, err := x509.MarshalPKCS8PrivateKey(&privateKey)
	if err != nil {
		panic(err)
	}

	pemBlock := &pem.Block{
		Type:  "PRIVATE KEY",
		Bytes: privKeyBytes,
	}

	var pemData []byte
	pemData = pem.EncodeToMemory(pemBlock)

	return string(pemData)
}