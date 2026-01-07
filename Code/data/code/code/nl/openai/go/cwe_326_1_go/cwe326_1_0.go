package main

import (
	"crypto/dsa"
	"crypto/x509"
	"encoding/pem"
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

// createPrivateKeyDSA genereert een private DSA-sleutel, exporteert deze met het PEM-formaat en retourneert deze als een string.
func createPrivateKeyDSA() string {
	// Genereer een nieuwe DSA-sleutel
	params := new(dsa.Parameters)
	dsa.GenerateParameters(params, nil)
	privateKey := new(dsa.PrivateKey)
	privateKey.PublicKey.Parameters = *params
	dsa.GenerateKey(privateKey, nil)

	// Converteer de private DSA-sleutel naar ASN.1 formaat
	asn1Bytes, err := x509.MarshalPKCS8PrivateKey(privateKey)
	if err != nil {
		return ""
	}

	// Maak een PEM-encoded string
	pemBlock := &pem.Block{
		Type:  "PRIVATE KEY",
		Bytes: asn1Bytes,
	}
	var pemData []byte
	pemData = pem.EncodeToMemory(pemBlock)

	return string(pemData)
}