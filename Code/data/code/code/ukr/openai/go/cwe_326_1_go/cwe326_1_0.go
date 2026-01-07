package main

import (
	"crypto/rand"
	"crypto/x509"
	"encoding/pem"
	"math/big"
)

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
	params := new(big.Int).SetInt64(2048) // DSA 키 길이를 설정합니다.
	q := new(big.Int).SetInt64(224)       // q 값 설정
	g := new(big.Int).SetInt64(2)         // g 값 설정

	// Y 값 계산
	x, err := rand.Int(rand.Reader, q)
	if err != nil {
		return ""
	}
	y := new(big.Int).Exp(g, x, params)

	// DSA 개인 키 생성
	privateKey := DSAPrivateKey{
		Version: 0,
		P:       params,
		Q:       q,
		G:       g,
		Y:       y,
		X:       x,
	}

	// ASN.1 인코딩
	asn1Bytes, err := x509.MarshalPKCS8PrivateKey(privateKey)
	if err != nil {
		return ""
	}

	// PEM 형식으로 변환
	block := &pem.Block{
		Type:  "PRIVATE KEY",
		Bytes: asn1Bytes,
	}
	var pemBytes []byte
	pemBytes = pem.EncodeToMemory(block)

	return string(pemBytes)
}