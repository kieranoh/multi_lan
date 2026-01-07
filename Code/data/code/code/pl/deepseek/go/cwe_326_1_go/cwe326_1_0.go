package main

import (
	"crypto/dsa"
	"crypto/rand"
	"encoding/asn1"
	"encoding/pem"
	"errors"
	"fmt"
	"math/big"
)

// DSAPrivateKey reprezentuje strukturę ASN.1 dla prywatnego klucza DSA
type DSAPrivateKey struct {
	Version int
	P       *big.Int
	Q       *big.Int
	G       *big.Int
	Y       *big.Int
	X       *big.Int
}

// Wygeneruj prywatny klucz DSA, wyeksportuj go w formacie PEM i zwróć jako ciąg.
func create_private_key_dsa() string {
	// Parametry DSA
	params := new(dsa.Parameters)

	// Generowanie parametrów DSA
	// Uwaga: dsa.GenerateParameters jest przestarzałe, ale używamy go dla zgodności
	// W praktyce należy używać crypto/ecdsa lub crypto/ed25519 dla nowych aplikacji
	err := dsa.GenerateParameters(params, rand.Reader, dsa.L1024N160)
	if err != nil {
		// W przypadku błędu zwracamy pusty ciąg
		return ""
	}

	// Generowanie klucza prywatnego DSA
	privateKey := new(dsa.PrivateKey)
	privateKey.PublicKey.Parameters = *params
	err = dsa.GenerateKey(privateKey, rand.Reader)
	if err != nil {
		return ""
	}

	// Konwersja do struktury DSAPrivateKey
	dsaPrivKey := DSAPrivateKey{
		Version: 0,
		P:       privateKey.P,
		Q:       privateKey.Q,
		G:       privateKey.G,
		Y:       privateKey.Y,
		X:       privateKey.X,
	}

	// Kodowanie ASN.1
	asn1Bytes, err := asn1.Marshal(dsaPrivKey)
	if err != nil {
		return ""
	}

	// Tworzenie bloku PEM
	pemBlock := &pem.Block{
		Type:  "DSA PRIVATE KEY",
		Bytes: asn1Bytes,
	}

	// Kodowanie do formatu PEM
	pemBytes := pem.EncodeToMemory(pemBlock)

	// Konwersja na ciąg i zwrócenie
	return string(pemBytes)
}