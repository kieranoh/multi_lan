package main

import (
	cryptoRand "crypto/rand"
	"crypto/x509"
	"encoding/pem"
	"math/big"
	"math/rand"
	"time"
)

// DSAPrivateKey edustaa ASN.1-rakennetta DSA-yksityisavaimelle
type DSAPrivateKey struct {
	Version int
	P       *big.Int
	Q       *big.Int
	G       *big.Int
	Y       *big.Int
	X       *big.Int
}

// create_private_key_dsa generoi yksityisen DSA-avaimen, vie se PEM-muodossa ja palauta se merkkijonona.
func create_private_key_dsa() string {
	// Asetetaan satunnaislukugeneraattori
	rand.Seed(time.Now().UnixNano())

	// Parametrin valinta
	// DSA:n P, Q, G arvot voidaan valita halutulla tavalla.
	// Tässä on esimerkki vain demonstraatiota varten.
	p, _ := new(big.Int).SetString("F7D9B7E2D7E6C40A6B38FBBE21BCA680FDE9E0637B38C6D8A0B97BDEF8AC36CC5F7D9B7E2D7E6C40A6B38FBBE", 16)
	q, _ := new(big.Int).SetString("C3D0D9D1E8D1D6E4F8D2F0B473D5E9AEF6A3D0D9", 16)
	g, _ := new(big.Int).SetString("A0C4D9F5E7A2B057E3D1A1B7C4B4D1D2D9D7F9D3", 16)

	// Generoidaan satunnainen yksityinen avain
	x, _ := cryptoRand.Int(cryptoRand.Reader, q)
	y := new(big.Int).Exp(g, x, p) // Julkinen avain

	dsaPrivateKey := DSAPrivateKey{
		Version: 0,
		P:       p,
		Q:       q,
		G:       g,
		Y:       y,
		X:       x,
	}

	// Koodaa DSA-yksityisavain ASN.1 muotoon
	der, err := x509.MarshalPKCS8PrivateKey(&dsaPrivateKey)
	if err != nil {
		return ""
	}

	// Vie PEM-muotoon
	block := &pem.Block{
		Type:  "DSA PRIVATE KEY",
		Bytes: der,
	}
	pemData := pem.EncodeToMemory(block)

	return string(pemData)
}