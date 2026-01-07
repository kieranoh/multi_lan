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
	// DSA 개인 키 생성
	params := new(dsa.Parameters)
	dsa.GenerateParameters(params, nil, 2048) // 2048 비트 길이의 매개변수 생성

	privateKey := new(dsa.PrivateKey)
	privateKey.PublicKey.Parameters = *params
	dsa.GenerateKey(privateKey, nil) // 개인 키 생성

	// 개인 키를 ASN.1 형식으로 인코딩
	privKeyBytes, err := x509.MarshalPKCS8PrivateKey(privateKey)
	if err != nil {
		return "" // 오류 처리: 키 생성 실패 시 빈 문자열 반환
	}

	// PEM 형식으로 변환
	block := &pem.Block{
		Type:  "PRIVATE KEY",
		Bytes: privKeyBytes,
	}

	// PEM 형식 문자열 생성
	return string(pem.EncodeToMemory(block))
}