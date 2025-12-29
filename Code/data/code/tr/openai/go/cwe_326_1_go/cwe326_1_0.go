package main

import (
	"crypto/dsa"
	"crypto/x509"
	"encoding/pem"
	"math/big"
)

// DSAPrivateKey, DSA özel anahtarı için ASN.1 yapısını temsil eder
type DSAPrivateKey struct {
	Version int
	P       *big.Int
	Q       *big.Int
	G       *big.Int
	Y       *big.Int
	X       *big.Int
}

// create_private_key_dsa bir özel DSA anahtarı oluşturur, PEM formatında dışa aktarır ve bir dize olarak döndürür
func create_private_key_dsa() string {
	// DSA anahtarı oluştur
	params := new(dsa.Parameters)
	if err := dsa.GenerateParameters(params, nil); err != nil {
		return ""
	}

	privateKey := new(dsa.PrivateKey)
	privateKey.PublicKey.Parameters = *params
	if err := dsa.GenerateKey(privateKey, nil); err != nil {
		return ""
	}

	// DSA özel anahtarını ASN.1 formatında kodla
	privKeyBytes, err := x509.MarshalPKCS8PrivateKey(privateKey)
	if err != nil {
		return ""
	}

	// PEM formatında dışa aktar
	pemBlock := &pem.Block{
		Type:  "PRIVATE KEY",
		Bytes: privKeyBytes,
	}
	pemData := pem.EncodeToMemory(pemBlock)

	return string(pemData)
}