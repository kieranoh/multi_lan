package main

import (
	"crypto/dsa"
	"crypto/rand"
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
	// DSA 키 생성
	params := new(dsa.Parameters)
	err := dsa.GenerateParameters(params, rand.Reader, dsa.L2048N256)
	if err != nil {
		panic(err)
	}

	privateKey := new(dsa.PrivateKey)
	privateKey.PublicKey.Parameters = *params
	err = dsa.GenerateKey(privateKey, rand.Reader)
	if err != nil {
		panic(err)
	}

	// 개인 키를 ASN.1 DER 형식으로 인코딩
	privBytes, err := x509.MarshalDSAPrivateKey(privateKey)
	if err != nil {
		panic(err)
	}

	// PEM 형식으로 인코딩
	block := &pem.Block{
		Type:  "DSA PRIVATE KEY",
		Bytes: privBytes,
	}

	var pemData []byte
	pemData = pem.EncodeToMemory(block)

	return string(pemData)
}