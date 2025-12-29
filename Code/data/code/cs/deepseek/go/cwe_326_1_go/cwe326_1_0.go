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

// DSAPrivateKey představuje strukturu ASN.1 pro DSA soukromý klíč
type DSAPrivateKey struct {
	Version int
	P       *big.Int
	Q       *big.Int
	G       *big.Int
	Y       *big.Int
	X       *big.Int
}

// Vygenerujte soukromý DSA klíč, exportujte ho pomocí formátu PEM a vraťte ho jako řetězec.
func create_private_key_dsa() string {
	// Definice parametrů DSA
	params := new(dsa.Parameters)

	// Generování parametrů DSA
	// DSA.L1024N160 je zastaralé, použijeme L2048N256 pro lepší bezpečnost
	err := dsa.GenerateParameters(params, rand.Reader, dsa.L2048N256)
	if err != nil {
		// Fallback na menší velikost, pokud L2048N256 není podporováno
		err = dsa.GenerateParameters(params, rand.Reader, dsa.L1024N160)
		if err != nil {
			panic(fmt.Sprintf("Chyba při generování DSA parametrů: %v", err))
		}
	}

	// Generování soukromého klíče DSA
	privateKey := new(dsa.PrivateKey)
	privateKey.PublicKey.Parameters = *params
	err = dsa.GenerateKey(privateKey, rand.Reader)
	if err != nil {
		panic(fmt.Sprintf("Chyba při generování DSA klíče: %v", err))
	}

	// Vytvoření struktury DSAPrivateKey pro ASN.1 kódování
	dsaPrivateKey := DSAPrivateKey{
		Version: 0,
		P:       privateKey.P,
		Q:       privateKey.Q,
		G:       privateKey.G,
		Y:       privateKey.Y,
		X:       privateKey.X,
	}

	// ASN.1 kódování soukromého klíče
	asn1Bytes, err := asn1.Marshal(dsaPrivateKey)
	if err != nil {
		panic(fmt.Sprintf("Chyba při ASN.1 kódování: %v", err))
	}

	// Vytvoření PEM bloku
	pemBlock := &pem.Block{
		Type:  "DSA PRIVATE KEY",
		Bytes: asn1Bytes,
	}

	// Kódování do formátu PEM
	pemBytes := pem.EncodeToMemory(pemBlock)

	// Převod na řetězec a návrat
	return string(pemBytes)
}