package main

import (
	"crypto/dsa"
	"crypto/rand"
	"encoding/asn1"
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

// Bir özel DSA anahtarı oluşturun, PEM formatında dışa aktarın ve bir dize olarak döndürün.
func create_private_key_dsa() string {
	// DSA parametreleri oluştur
	params := new(dsa.Parameters)

	// L=2048, N=256 olacak şekilde parametreleri oluştur
	// crypto/dsa paketi GenerateParameters fonksiyonu ile
	err := dsa.GenerateParameters(params, rand.Reader, dsa.L2048N256)
	if err != nil {
		return ""
	}

	// Özel anahtar oluştur
	privateKey := new(dsa.PrivateKey)
	privateKey.PublicKey.Parameters = *params
	err = dsa.GenerateKey(privateKey, rand.Reader)
	if err != nil {
		return ""
	}

	// DSAPrivateKey yapısını doldur
	dsaPrivKey := DSAPrivateKey{
		Version: 0,
		P:       privateKey.P,
		Q:       privateKey.Q,
		G:       privateKey.G,
		Y:       privateKey.Y,
		X:       privateKey.X,
	}

	// ASN.1 kodlaması
	asn1Bytes, err := asn1.Marshal(dsaPrivKey)
	if err != nil {
		return ""
	}

	// PEM bloğu oluştur
	pemBlock := &pem.Block{
		Type:  "DSA PRIVATE KEY",
		Bytes: asn1Bytes,
	}

	// PEM formatına dönüştür
	pemBytes := pem.EncodeToMemory(pemBlock)

	return string(pemBytes)
}