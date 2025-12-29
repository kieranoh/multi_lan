package main

import (
	"crypto/rand"
	"crypto/x509"
	"encoding/pem"
	"math/big"
)

// DSAPrivateKey representa l'estructura ASN.1 per a la clau privada DSA
type DSAPrivateKey struct {
	Version int
	P       *big.Int
	Q       *big.Int
	G       *big.Int
	Y       *big.Int
	X       *big.Int
}

// create_private_key_dsa genera una clau privada DSA, exporta-la utilitzant el format PEM i retorna-la com una cadena.
func create_private_key_dsa() string {
	params := new(big.Int).SetInt64(2048) // DSA key size
	x, err := rand.Int(rand.Reader, params)
	if err != nil {
		panic(err) // Handle error appropriately
	}

	dsa := DSAPrivateKey{
		Version: 0,
		P:       params, // P would be generated based on DSA parameters
		Q:       big.NewInt(0), // Q should be generated
		G:       big.NewInt(0), // G should be generated
		Y:       big.NewInt(0), // Y should be calculated from G^X mod P
		X:       x,
	}

	privBytes, err := x509.MarshalPKCS8PrivateKey(&dsa)
	if err != nil {
		panic(err) // Handle error appropriately
	}

	pemBlock := &pem.Block{
		Type:  "PRIVATE KEY",
		Bytes: privBytes,
	}

	pemData := pem.EncodeToMemory(pemBlock)
	return string(pemData)
}