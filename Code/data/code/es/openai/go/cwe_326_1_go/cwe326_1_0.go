package main

import (
	"crypto/dsa"
	"crypto/rand"
	"encoding/pem"
	"math/big"
)

// DSAPrivateKey representa la estructura ASN.1 para la clave privada DSA
type DSAPrivateKey struct {
	Version int
	P       *big.Int
	Q       *big.Int
	G       *big.Int
	Y       *big.Int
	X       *big.Int
}

// create_private_key_dsa genera una clave privada DSA, expórtala usando el formato PEM y devuélvela como una cadena.
func create_private_key_dsa() string {
	// Generar una nueva clave DSA
	params := new(dsa.Parameters)
	err := dsa.GenerateParameters(params, rand.Reader, dsa.L2048N256)
	if err != nil {
		return ""
	}

	privateKey := new(dsa.PrivateKey)
	privateKey.PublicKey.Parameters = *params
	err = dsa.GenerateKey(privateKey, rand.Reader)
	if err != nil {
		return ""
	}

	// Convertir la clave privada a la estructura DSAPrivateKey
	dsaPrivateKey := DSAPrivateKey{
		Version: 0,
		P:       privateKey.PublicKey.P,
		Q:       privateKey.PublicKey.Q,
		G:       privateKey.PublicKey.G,
		Y:       privateKey.PublicKey.Y,
		X:       privateKey.X,
	}

	// Codificar la clave DSA en formato PEM
	privKeyDER, err := x509.MarshalPKCS8PrivateKey(privateKey)
	if err != nil {
		return ""
	}

	pemBlock := &pem.Block{
		Type:  "PRIVATE KEY",
		Bytes: privKeyDER,
	}

	var pemBytes []byte
	pemBytes = pem.EncodeToMemory(pemBlock)

	return string(pemBytes)
}