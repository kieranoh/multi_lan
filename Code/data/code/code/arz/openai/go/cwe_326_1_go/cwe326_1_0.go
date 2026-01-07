package main

import (
	"crypto/rand"
	"crypto/x509"
	"encoding/pem"
	"math/big"
	"os"

	"golang.org/x/crypto/sha3"
	"golang.org/x/crypto/dsa"
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

// create_private_key_dsa는 개인 DSA 키를 생성하고, PEM 형식을 사용하여 내보낸 다음, 문자열로 반환합니다.
func create_private_key_dsa() string {
	// DSA 키 생성
	params := new(dsa.Parameters)
	if err := dsa.GenerateParameters(params, rand.Reader, dsa.L2048N256); err != nil {
		return ""
	}

	privateKey := new(dsa.PrivateKey)
	privateKey.PublicKey.Parameters = *params
	if err := dsa.GenerateKey(privateKey, rand.Reader); err != nil {
		return ""
	}

	// 개인 키를 ASN.1 형식으로 인코딩
	asn1Bytes, err := x509.MarshalPKCS8PrivateKey(privateKey)
	if err != nil {
		return ""
	}

	// PEM 인코딩
	pemBlock := &pem.Block{
		Type:  "PRIVATE KEY",
		Bytes: asn1Bytes,
	}
	var pemData []byte
	pemData = pem.EncodeToMemory(pemBlock)

	// 문자열로 반환
	return string(pemData)
}