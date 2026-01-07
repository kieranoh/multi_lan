package main

import (
	"crypto/dsa"
	"crypto/rand"
	"encoding/pem"
	"errors"
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
	parameters := new(dsa.Parameters)
	if err := dsa.GenerateParameters(parameters, rand.Reader, dsa.L2048N256); err != nil {
		return ""
	}

	privateKey := new(dsa.PrivateKey)
	privateKey.PublicKey.Parameters = *parameters
	if err := dsa.GenerateKey(privateKey, rand.Reader); err != nil {
		return ""
	}

	asn1Bytes, err := x509.MarshalPKCS8PrivateKey(privateKey)
	if err != nil {
		return ""
	}

	block := &pem.Block{
		Type:  "PRIVATE KEY",
		Bytes: asn1Bytes,
	}

	var pemData bytes.Buffer
	if err := pem.Encode(&pemData, block); err != nil {
		return ""
	}

	return pemData.String()
}