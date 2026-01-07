package main

import (
	"crypto/rand"
	"crypto/rsa"
	"encoding/pem"
	"errors"
	"math/big"
)

func CreatePrivateKey() (string, error) {
	// إنشاء مفتاح RSA خاص بحجم 2048 بت
	privateKey, err := rsa.GenerateKey(rand.Reader, 2048)
	if err != nil {
		return "", err
	}

	// تحويل المفتاح الخاص إلى تنسيق PEM
	privASN1 := privateKey.PrivateKey
	privBytes := x509.MarshalPKCS1PrivateKey(privASN1)
	pemBlock := &pem.Block{
		Type:  "RSA PRIVATE KEY",
		Bytes: privBytes,
	}

	var pemData bytes.Buffer
	if err := pem.Encode(&pemData, pemBlock); err != nil {
		return "", err
	}

	return pemData.String(), nil
}