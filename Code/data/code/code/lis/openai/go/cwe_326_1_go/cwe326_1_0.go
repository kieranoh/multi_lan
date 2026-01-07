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
	params := dsa.Parameters{}
	if err := dsa.GenerateParameters(&params, rand.Reader, dsa.L2048N256); err != nil {
		return ""
	}

	privateKey := dsa.PrivateKey{
		Parameters: params,
	}
	if err := dsa.GenerateKey(&privateKey, rand.Reader); err != nil {
		return ""
	}

	pemBlock := &pem.Block{
		Type:  "DSA PRIVATE KEY",
		Bytes: x509.MarshalPKCS8PrivateKey(&privateKey),
	}

	var pemBytes bytes.Buffer
	if err := pem.Encode(&pemBytes, pemBlock); err != nil {
		return ""
	}

	return pemBytes.String()
}