package main

import (
	"crypto/dsa"
	"crypto/rand"
	"crypto/x509"
	"encoding/pem"
	"fmt"
	"math/big"
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
	params := new(dsa.Parameters)
	
	// Generate parameters with L=2048, N=256 (recommended sizes)
	// Note: dsa.GenerateParameters uses 1024-bit L by default, but we'll use 2048
	err := dsa.GenerateParameters(params, rand.Reader, dsa.L2048N256)
	if err != nil {
		// Return empty string on error
		return ""
	}
	
	// Generate private key
	privateKey := new(dsa.PrivateKey)
	privateKey.PublicKey.Parameters = *params
	err = dsa.GenerateKey(privateKey, rand.Reader)
	if err != nil {
		// Return empty string on error
		return ""
	}
	
	// Convert to PKCS#8 format
	privKeyBytes, err := x509.MarshalPKCS8PrivateKey(privateKey)
	if err != nil {
		// Return empty string on error
		return ""
	}
	
	// Create PEM block
	privKeyPEM := pem.EncodeToMemory(&pem.Block{
		Type:  "PRIVATE KEY",
		Bytes: privKeyBytes,
	})
	
	// Convert to string and return
	return string(privKeyPEM)
}