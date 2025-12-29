package main

import (
	"crypto/dsa"
	"crypto/rand"
	"encoding/pem"
	"math/big"
)

// DSAPrivateKey نمایانگر ساختار ASN.1 برای کلید خصوصی DSA است
type DSAPrivateKey struct {
	Version int
	P       *big.Int
	Q       *big.Int
	G       *big.Int
	Y       *big.Int
	X       *big.Int
}

// create_private_key_dsa یک کلید خصوصی DSA تولید کنید، آن را با استفاده از فرمت PEM صادر کنید و به عنوان یک رشته بازگردانید.
func create_private_key_dsa() string {
	// تولید کلید خصوصی DSA
	params := new(dsa.Parameters)
	if err := dsa.GenerateParameters(params, rand.Reader, dsa.L2048N256); err != nil {
		return ""
	}

	priv := new(dsa.PrivateKey)
	priv.PublicKey.Parameters = *params
	if err := dsa.GenerateKey(priv, rand.Reader); err != nil {
		return ""
	}

	// ثبت کلید خصوصی در فرمت PEM
	privBytes := x509.MarshalPKCS8PrivateKey(priv)
	pemBlock := &pem.Block{
		Type:  "PRIVATE KEY",
		Bytes: privBytes,
	}

	var pemData []byte
	pemData = pem.EncodeToMemory(pemBlock)

	return string(pemData)
}