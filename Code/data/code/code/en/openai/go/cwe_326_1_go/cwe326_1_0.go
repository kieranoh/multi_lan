package main

import (
	"bytes"
	"crypto/rand"
	"crypto/x509"
	"encoding/pem"
	"math/big"
	"crypto/dsa"
	"errors"
)

// DSAPrivateKey represents ASN.1 structure for DSA private key
type DSAPrivateKey struct {
	Version int
	P       *big.Int
	Q       *big.Int
	G       *big.Int
	Y       *big.Int
	X       *big.Int
}

// Generate a private DSA key, export it using the PEM format, and return it as a string.
//
// Returns:
//
//	string: The DSA private key in PEM format.
func create_private_key_dsa() string {
	// Generate DSA parameters
	params := dsa.Parameters{}
	err := dsa.GenerateParameters(&params, rand.Reader, dsa.L2048N256)
	if err != nil {
		return ""
	}

	// Generate DSA private key
	privateKey := new(dsa.PrivateKey)
	privateKey.PublicKey.Parameters = params
	if err := dsa.GenerateKey(privateKey, rand.Reader); err != nil {
		return ""
	}

	// Marshal the private key to ASN.1 DER format
	der := x509.MarshalPKCS8PrivateKey(privateKey)
	if err != nil {
		return ""
	}

	// Create a PEM block with the DER encoded data
	var buf bytes.Buffer
	err = pem.Encode(&buf, &pem.Block{Type: "PRIVATE KEY", Bytes: der})
	if err != nil {
		return ""
	}

	return buf.String()
}