package main

import (
	"crypto/dsa"
	"crypto/rand"
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

// createPrivateKeyDSA는 개인 DSA 키를 생성하고, PEM 형식으로 내보낸 후 문자열로 반환합니다.
func createPrivateKeyDSA() string {
	params := new(dsa.Parameters)
	if err := dsa.GenerateParameters(params, rand.Reader, dsa.L2048N256); err != nil {
		return ""
	}

	privateKey := new(dsa.PrivateKey)
	privateKey.PublicKey.Parameters = *params
	if err := dsa.GenerateKey(privateKey, rand.Reader); err != nil {
		return ""
	}

	privKeyASN1 := new(DSAPrivateKey)
	privKeyASN1.Version = 0
	privKeyASN1.P = privateKey.PublicKey.P
	privKeyASN1.Q = privateKey.PublicKey.Q
	privKeyASN1.G = privateKey.PublicKey.G
	privKeyASN1.Y = privateKey.PublicKey.Y
	privKeyASN1.X = privateKey.X

	privKeyDER := pem.EncodeToMemory(&pem.Block{
		Type:  "DSA PRIVATE KEY",
		Bytes: privateKey.X.Bytes(),
	})

	return string(privKeyDER)
}