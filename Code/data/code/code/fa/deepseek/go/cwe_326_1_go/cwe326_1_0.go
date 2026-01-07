package main

import (
	"crypto/dsa"
	"crypto/rand"
	"crypto/x509"
	"encoding/asn1"
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

// یک کلید خصوصی DSA تولید کنید، آن را با استفاده از فرمت PEM صادر کنید و به عنوان یک رشته بازگردانید.
func create_private_key_dsa() string {
	// پارامترهای DSA را تولید می‌کنیم
	params := new(dsa.Parameters)
	
	// اندازه کلید 2048 بیت انتخاب می‌کنیم (مطابق با استانداردهای امنیتی فعلی)
	err := dsa.GenerateParameters(params, rand.Reader, dsa.L2048N256)
	if err != nil {
		return ""
	}
	
	// کلید خصوصی DSA را تولید می‌کنیم
	privateKey := new(dsa.PrivateKey)
	privateKey.PublicKey.Parameters = *params
	err = dsa.GenerateKey(privateKey, rand.Reader)
	if err != nil {
		return ""
	}
	
	// کلید خصوصی را به فرمت ASN.1 تبدیل می‌کنیم
	dsaPrivateKey := DSAPrivateKey{
		Version: 0,
		P:       privateKey.P,
		Q:       privateKey.Q,
		G:       privateKey.G,
		Y:       privateKey.Y,
		X:       privateKey.X,
	}
	
	// ساختار ASN.1 را کدگذاری می‌کنیم
	asn1Bytes, err := asn1.Marshal(dsaPrivateKey)
	if err != nil {
		return ""
	}
	
	// بلوک PEM ایجاد می‌کنیم
	pemBlock := &pem.Block{
		Type:  "DSA PRIVATE KEY",
		Bytes: asn1Bytes,
	}
	
	// بلوک PEM را به رشته تبدیل می‌کنیم
	pemString := string(pem.EncodeToMemory(pemBlock))
	
	return pemString
}