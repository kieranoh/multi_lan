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

// create_private_key_dsa는 개인 DSA 키를 생성하고, PEM 형식을 사용하여 내보낸 다음, 문자열로 반환합니다.
func create_private_key_dsa() (string, error) {
	parameterSizes := 2048 // DSA 키 크기 (2048 비트)
	priv := new(dsa.PrivateKey)

	// DSA 개인 키 생성
	if err := dsa.GenerateParameters(&priv.Parameters, rand.Reader, parameterSizes); err != nil {
		return "", err
	}
	if err := dsa.GenerateKey(priv, rand.Reader); err != nil {
		return "", err
	}

	// PEM 형식으로 개인 키 내보내기
	privKeyASN1, err := x509.MarshalPKCS8PrivateKey(priv)
	if err != nil {
		return "", err
	}
	
	block := &pem.Block{
		Type:  "PRIVATE KEY",
		Bytes: privKeyASN1,
	}
	
	var pemBuffer bytes.Buffer
	if err := pem.Encode(&pemBuffer, block); err != nil {
		return "", err
	}
	
	return pemBuffer.String(), nil
}