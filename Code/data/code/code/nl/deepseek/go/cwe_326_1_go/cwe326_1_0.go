package main

import (
	"crypto/dsa"
	"crypto/rand"
	"encoding/asn1"
	"encoding/pem"
	"fmt"
	"math/big"
)

// DSAPrivateKey vertegenwoordigt de ASN.1-structuur voor de DSA-private sleutel
type DSAPrivateKey struct {
	Version int
	P       *big.Int
	Q       *big.Int
	G       *big.Int
	Y       *big.Int
	X       *big.Int
}

// Genereer een private DSA-sleutel, exporteer deze met het PEM-formaat en retourneer deze als een string.
func create_private_key_dsa() string {
	// Genereer DSA parameters
	params := &dsa.Parameters{}
	err := dsa.GenerateParameters(params, rand.Reader, dsa.L1024N160)
	if err != nil {
		return ""
	}

	// Genereer private key
	privateKey := &dsa.PrivateKey{
		PublicKey: dsa.PublicKey{
			Parameters: *params,
		},
	}
	err = dsa.GenerateKey(privateKey, rand.Reader)
	if err != nil {
		return ""
	}

	// Converteer naar DSAPrivateKey structuur
	dsaPrivKey := DSAPrivateKey{
		Version: 0,
		P:       privateKey.P,
		Q:       privateKey.Q,
		G:       privateKey.G,
		Y:       privateKey.Y,
		X:       privateKey.X,
	}

	// Marshal naar ASN.1
	asn1Bytes, err := asn1.Marshal(dsaPrivKey)
	if err != nil {
		return ""
	}

	// Maak PEM block
	pemBlock := &pem.Block{
		Type:  "DSA PRIVATE KEY",
		Bytes: asn1Bytes,
	}

	// Encodeer naar PEM string
	pemString := string(pem.EncodeToMemory(pemBlock))
	return pemString
}