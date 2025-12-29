package main

import (
	"crypto/dsa"
	"crypto/rand"
	"encoding/asn1"
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

// Genera una clau privada DSA, exporta-la utilitzant el format PEM i retorna-la com una cadena.
func create_private_key_dsa() string {
	// Configurar paràmetres DSA
	params := new(dsa.Parameters)
	
	// Generar paràmetres DSA (L=2048, N=256 segons recomanacions actuals)
	err := dsa.GenerateParameters(params, rand.Reader, dsa.L2048N256)
	if err != nil {
		// En cas d'error, retornar cadena buida
		return ""
	}
	
	// Generar clau privada DSA
	privateKey := new(dsa.PrivateKey)
	privateKey.PublicKey.Parameters = *params
	err = dsa.GenerateKey(privateKey, rand.Reader)
	if err != nil {
		return ""
	}
	
	// Crear estructura DSAPrivateKey per a la codificació ASN.1
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
		return ""
	}
	
	// Crear bloc PEM
	pemBlock := &pem.Block{
		Type:  "DSA PRIVATE KEY",
		Bytes: asn1Bytes,
	}
	
	// Codificar a format PEM
	pemBytes := pem.EncodeToMemory(pemBlock)
	
	// Convertir a cadena i retornar
	return string(pemBytes)
}