package main

import (
	"crypto/rand"
	"crypto/x509"
	"encoding/pem"
	"math/big"
	"os"
)

// DSAPrivateKey az ASN.1 struktúrát képviseli a DSA privát kulcs számára
type DSAPrivateKey struct {
	Version int
	P       *big.Int
	Q       *big.Int
	G       *big.Int
	Y       *big.Int
	X       *big.Int
}

// create_private_key_dsa generálj egy privát DSA kulcsot, exportáld PEM formátumban, és térj vissza vele stringként.
func create_private_key_dsa() string {
	params := new(big.Int)
	q := new(big.Int).Lsh(big.NewInt(1), 160)
	p := new(big.Int).Lsh(q, 1)
	g := new(big.Int).Exp(big.NewInt(2), big.NewInt(2), p)

	x, err := rand.Int(rand.Reader, q)
	if err != nil {
		return ""
	}

	y := new(big.Int).Exp(g, x, p)

	privateKey := DSAPrivateKey{
		Version: 0,
		P:       p,
		Q:       q,
		G:       g,
		Y:       y,
		X:       x,
	}

	privKeyBytes, err := x509.MarshalDSAPrivateKey(&privateKey)
	if err != nil {
		return ""
	}

	pemBlock := &pem.Block{
		Type:  "DSA PRIVATE KEY",
		Bytes: privKeyBytes,
	}
	pemBytes := pem.EncodeToMemory(pemBlock)

	return string(pemBytes)
}