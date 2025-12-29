package main

import (
	"crypto/dsa"
	"crypto/rand"
	"encoding/pem"
	"fmt"
	"math/big"
)

// يمثل DSAPrivateKey هيكل ASN.1 لمفتاح DSA الخاص
type DSAPrivateKey struct {
	Version int
	P       *big.Int
	Q       *big.Int
	G       *big.Int
	Y       *big.Int
	X       *big.Int
}

// قم بإنشاء مفتاح DSA خاص، وقم بتصديره باستخدام تنسيق PEM، وأرجعه كسلسلة نصية.
func create_private_key_dsa() string {
	// إنشاء مفتاح DSA جديد
	privKey := new(dsa.PrivateKey)
	params := new(dsa.Parameters)

	// توليد معلمات DSA
	if err := dsa.GenerateParameters(params, rand.Reader, dsa.L2048N256); err != nil {
		return fmt.Sprintf("خطأ في توليد المعلمات: %v", err)
	}

	// توليد مفتاح خاص
	if err := privKey.GenerateKey(rand.Reader); err != nil {
		return fmt.Sprintf("خطأ في توليد المفتاح: %v", err)
	}

	// تحويل المفتاح الخاص إلى هيكل DSAPrivateKey
	dsaPrivKey := DSAPrivateKey{
		Version: 0,
		P:       privKey.PublicKey.Parameters.P,
		Q:       privKey.PublicKey.Parameters.Q,
		G:       privKey.PublicKey.Parameters.G,
		Y:       privKey.PublicKey.Y,
		X:       privKey.X,
	}

	// تشفير المفتاح الخاص في تنسيق PEM
	privKeyBytes := x509.MarshalPKCS8PrivateKey(privKey)
	block := &pem.Block{
		Type:  "DSA PRIVATE KEY",
		Bytes: privKeyBytes,
	}

	var pemData bytes.Buffer
	if err := pem.Encode(&pemData, block); err != nil {
		return fmt.Sprintf("خطأ في التشفير إلى PEM: %v", err)
	}

	// إرجاع سلسلة نصية تحتوي على مفتاح DSA الخاص بصيغة PEM
	return pemData.String()
}