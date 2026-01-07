package main

import (
	"crypto/dsa"
	"crypto/x509"
	"encoding/pem"
	"math/big"
)

// DSAPrivateKey는 DSA 개인 키에 대한 ASN.1 구조를 나타냅니다.
type DSAPrivateKey struct {
	Version int
	P       *big.Int
	Q       *big.Int
	G       *big.Int
	Y       *big.Int
	X       *big.Int
}

// 개인 DSA 키를 생성하고, PEM 형식을 사용하여 내보낸 다음, 문자열로 반환합니다.
func create_private_key_dsa() string {
	priv := new(dsa.PrivateKey)
	if err := dsa.GenerateParameters(&priv.Parameters, dsa.L2048N256, nil); err != nil {
		return ""
	}
	if err := dsa.GenerateKey(priv, nil); err != nil {
		return ""
	}

	asn1Encoded, err := x509.MarshalPKCS8PrivateKey(priv)
	if err != nil {
		return ""
	}

	pemBlock := &pem.Block{
		Type:  "PRIVATE KEY",
		Bytes: asn1Encoded,
	}
	var pemData []byte
	pemData = pem.EncodeToMemory(pemBlock)

	return string(pemData)
}