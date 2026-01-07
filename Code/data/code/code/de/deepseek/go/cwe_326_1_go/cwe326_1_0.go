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

// DSAPrivateKey repräsentiert die ASN.1-Struktur für den DSA-Privatschlüssel
type DSAPrivateKey struct {
	Version int
	P       *big.Int
	Q       *big.Int
	G       *big.Int
	Y       *big.Int
	X       *big.Int
}

// Generiere einen privaten DSA-Schlüssel, exportiere ihn im PEM-Format und gebe ihn als String zurück.
func create_private_key_dsa() string {
	// DSA-Parameter generieren
	params := new(dsa.Parameters)
	
	// Parameter L2048N256 gemäß FIPS 186-4
	err := dsa.GenerateParameters(params, rand.Reader, dsa.L2048N256)
	if err != nil {
		return fmt.Sprintf("Fehler beim Generieren der DSA-Parameter: %v", err)
	}

	// Privaten DSA-Schlüssel generieren
	privateKey := new(dsa.PrivateKey)
	privateKey.PublicKey.Parameters = *params
	err = dsa.GenerateKey(privateKey, rand.Reader)
	if err != nil {
		return fmt.Sprintf("Fehler beim Generieren des DSA-Schlüssels: %v", err)
	}

	// DSA-PrivateKey in ASN.1-Struktur konvertieren
	dsaPrivateKey := DSAPrivateKey{
		Version: 0,
		P:       privateKey.P,
		Q:       privateKey.Q,
		G:       privateKey.G,
		Y:       privateKey.Y,
		X:       privateKey.X,
	}

	// ASN.1-Marshalling durchführen
	asn1Bytes, err := asn1.Marshal(dsaPrivateKey)
	if err != nil {
		return fmt.Sprintf("Fehler beim ASN.1-Marshalling: %v", err)
	}

	// PEM-Block erstellen
	pemBlock := &pem.Block{
		Type:  "DSA PRIVATE KEY",
		Bytes: asn1Bytes,
	}

	// PEM in String konvertieren
	pemString := string(pem.EncodeToMemory(pemBlock))
	
	return pemString
}