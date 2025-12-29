package main

import (
	"crypto/dsa"
	"crypto/rand"
	"crypto/x509"
	"encoding/asn1"
	"encoding/pem"
	"errors"
	"fmt"
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

// Genera una clave privada DSA, expórtala usando el formato PEM y devuélvela como una cadena.
func create_private_key_dsa() string {
	// Definir parámetros DSA
	params := &dsa.Parameters{}
	
	// Generar parámetros DSA con L=2048, N=256 (recomendaciones modernas)
	err := dsa.GenerateParameters(params, rand.Reader, dsa.L2048N256)
	if err != nil {
		panic(fmt.Sprintf("Error al generar parámetros DSA: %v", err))
	}
	
	// Generar clave privada DSA
	privateKey := &dsa.PrivateKey{
		PublicKey: dsa.PublicKey{
			Parameters: *params,
		},
	}
	
	err = dsa.GenerateKey(privateKey, rand.Reader)
	if err != nil {
		panic(fmt.Sprintf("Error al generar clave DSA: %v", err))
	}
	
	// Crear estructura DSAPrivateKey personalizada
	dsaPrivKey := DSAPrivateKey{
		Version: 0,
		P:       privateKey.P,
		Q:       privateKey.Q,
		G:       privateKey.G,
		Y:       privateKey.Y,
		X:       privateKey.X,
	}
	
	// Codificar a ASN.1
	asn1Bytes, err := asn1.Marshal(dsaPrivKey)
	if err != nil {
		panic(fmt.Sprintf("Error al codificar ASN.1: %v", err))
	}
	
	// Crear bloque PEM
	pemBlock := &pem.Block{
		Type:  "DSA PRIVATE KEY",
		Bytes: asn1Bytes,
	}
	
	// Codificar a PEM
	pemBytes := pem.EncodeToMemory(pemBlock)
	
	return string(pemBytes)
}