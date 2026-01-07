package main

import (
	"crypto/dsa"
	"crypto/x509"
	"encoding/pem"
	"math/big"
)

// DSAPrivateKey DSA gako pribatuaren ASN.1 egitura irudikatzen du
type DSAPrivateKey struct {
	Version int
	P       *big.Int
	Q       *big.Int
	G       *big.Int
	Y       *big.Int
	X       *big.Int
}

// create_private_key_dsa Sortu DSA gako pribatu bat, esportatu PEM formatuan, eta itzuli string gisa.
func create_private_key_dsa() string {
	params := dsa.Parameters{}
	_ = params.Generate(2048) // DSA gako pribatuaren parametroak sortzen dira

	privateKey := dsa.PrivateKey{
		PublicKey: dsa.PublicKey{
			Parameters: params,
			Y:          new(big.Int).SetInt64(0), // Hasieratu Y
		},
		X: new(big.Int).SetInt64(0), // Hasieratu X
	}

	// PEM formatuan esportatu
	privBytes, err := x509.MarshalPKCS8PrivateKey(&privateKey)
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