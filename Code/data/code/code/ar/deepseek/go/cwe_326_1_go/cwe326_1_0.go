package main

import (
	"crypto/dsa"
	"crypto/rand"
	"crypto/x509"
	"encoding/asn1"
	"encoding/pem"
	"fmt"
	"math/big"
)

// DSAPrivateKey يمثل هيكل ASN.1 لمفتاح DSA الخاص
type DSAPrivateKey struct {
	Version int
	P       *big.Int
	Q       *big.Int
	G       *big.Int
	Y       *big.Int
	X       *big.Int
}

// create_private_key_dsa تقوم بإنشاء مفتاح DSA خاص، وتصديره باستخدام تنسيق PEM، وإرجاعه كسلسلة نصية
func create_private_key_dsa() string {
	// إنشاء معلمات DSA
	params := new(dsa.Parameters)
	
	// توليد معلمات DSA (P، Q، G)
	// ملاحظة: L2048، N256 هو حجم شائع وآمن لـ DSA
	err := dsa.GenerateParameters(params, rand.Reader, dsa.L2048N256)
	if err != nil {
		return fmt.Sprintf("فشل في توليد معلمات DSA: %v", err)
	}
	
	// إنشاء مفتاح DSA خاص
	privateKey := new(dsa.PrivateKey)
	privateKey.PublicKey.Parameters = *params
	
	// توليد المفتاح الخاص
	err = dsa.GenerateKey(privateKey, rand.Reader)
	if err != nil {
		return fmt.Sprintf("فشل في توليد المفتاح الخاص: %v", err)
	}
	
	// تحويل المفتاح الخاص إلى تنسيق ASN.1
	dsaPrivKey := DSAPrivateKey{
		Version: 0,
		P:       privateKey.P,
		Q:       privateKey.Q,
		G:       privateKey.G,
		Y:       privateKey.Y,
		X:       privateKey.X,
	}
	
	// ترميز المفتاح الخاص إلى ASN.1 DER
	derBytes, err := asn1.Marshal(dsaPrivKey)
	if err != nil {
		return fmt.Sprintf("فشل في ترميز المفتاح الخاص: %v", err)
	}
	
	// إنشاء كتلة PEM
	pemBlock := &pem.Block{
		Type:  "DSA PRIVATE KEY",
		Bytes: derBytes,
	}
	
	// ترميز كتلة PEM إلى سلسلة نصية
	pemString := string(pem.EncodeToMemory(pemBlock))
	
	return pemString
}