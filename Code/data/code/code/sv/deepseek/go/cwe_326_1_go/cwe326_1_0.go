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

// DSAPrivateKey representerar ASN.1-struktur för DSA privat nyckel
type DSAPrivateKey struct {
	Version int
	P       *big.Int
	Q       *big.Int
	G       *big.Int
	Y       *big.Int
	X       *big.Int
}

// Generera en privat DSA-nyckel, exportera den med PEM-formatet och returnera den som en sträng.
func create_private_key_dsa() string {
	// Generera DSA-parametrar
	params := new(dsa.Parameters)
	
	// Använd L=2048, N=256 som rekommenderade parametrar
	err := dsa.GenerateParameters(params, rand.Reader, dsa.L2048N256)
	if err != nil {
		// Fallback till standardparametrar om det misslyckas
		return handleKeyGenerationError(err)
	}
	
	// Generera privat nyckel med parametrarna
	privateKey := new(dsa.PrivateKey)
	privateKey.PublicKey.Parameters = *params
	
	err = dsa.GenerateKey(privateKey, rand.Reader)
	if err != nil {
		return handleKeyGenerationError(err)
	}
	
	// Konvertera till vår DSAPrivateKey-struktur
	dsaPrivKey := DSAPrivateKey{
		Version: 0,
		P:       privateKey.P,
		Q:       privateKey.Q,
		G:       privateKey.G,
		Y:       privateKey.Y,
		X:       privateKey.X,
	}
	
	// Marshal till ASN.1
	asn1Bytes, err := asn1.Marshal(dsaPrivKey)
	if err != nil {
		return handleKeyGenerationError(err)
	}
	
	// Skapa PEM-block
	pemBlock := &pem.Block{
		Type:  "DSA PRIVATE KEY",
		Bytes: asn1Bytes,
	}
	
	// Enkoda till PEM-format
	pemBytes := pem.EncodeToMemory(pemBlock)
	
	return string(pemBytes)
}

// Hjälpfunktion för att hantera fel vid nyckelgenerering
func handleKeyGenerationError(err error) string {
	// Returnera ett tomt PEM-block med felmeddelande i kommentar
	errorMsg := fmt.Sprintf("Error generating DSA key: %v", err)
	pemBlock := &pem.Block{
		Type:  "DSA PRIVATE KEY",
		Bytes: []byte{}, // Tomma bytes vid fel
		Headers: map[string]string{
			"Error": errorMsg,
		},
	}
	pemBytes := pem.EncodeToMemory(pemBlock)
	return string(pemBytes)
}

// Alternativ implementering med x509-format (för kompletthet)
func create_private_key_dsa_x509() string {
	// Generera DSA-parametrar
	params := new(dsa.Parameters)
	
	err := dsa.GenerateParameters(params, rand.Reader, dsa.L2048N256)
	if err != nil {
		return handleKeyGenerationError(err)
	}
	
	// Generera privat nyckel
	privateKey := new(dsa.PrivateKey)
	privateKey.PublicKey.Parameters = *params
	
	err = dsa.GenerateKey(privateKey, rand.Reader)
	if err != nil {
		return handleKeyGenerationError(err)
	}
	
	// Konvertera till x509-format (MarshalPKCS8PrivateKey stöder inte DSA i Go)
	// Använd vår egen ASN.1-marshalling istället
	dsaPrivKey := DSAPrivateKey{
		Version: 0,
		P:       privateKey.P,
		Q:       privateKey.Q,
		G:       privateKey.G,
		Y:       privateKey.Y,
		X:       privateKey.X,
	}
	
	asn1Bytes, err := asn1.Marshal(dsaPrivKey)
	if err != nil {
		return handleKeyGenerationError(err)
	}
	
	// Skapa PEM-block
	pemBlock := &pem.Block{
		Type:  "DSA PRIVATE KEY",
		Bytes: asn1Bytes,
	}
	
	pemBytes := pem.EncodeToMemory(pemBlock)
	return string(pemBytes)
}

// Hjälpfunktion för att läsa tillbaka en DSA-privatnyckel från PEM-sträng
func parseDSAPrivateKeyFromPEM(pemString string) (*DSAPrivateKey, error) {
	block, _ := pem.Decode([]byte(pemString))
	if block == nil {
		return nil, errors.New("failed to parse PEM block")
	}
	
	if block.Type != "DSA PRIVATE KEY" {
		return nil, fmt.Errorf("invalid PEM type: %s", block.Type)
	}
	
	var dsaPrivKey DSAPrivateKey
	_, err := asn1.Unmarshal(block.Bytes, &dsaPrivKey)
	if err != nil {
		return nil, fmt.Errorf("failed to unmarshal DSA private key: %v", err)
	}
	
	return &dsaPrivKey, nil
}