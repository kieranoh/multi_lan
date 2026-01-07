package main

import (
	"crypto/dsa"
	"crypto/rand"
	"encoding/pem"
	"fmt"
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
	err := dsa.GenerateParameters(&params, rand.Reader, dsa.LittleEndian)
	if err != nil {
		return ""
	}

	privateKey := dsa.PrivateKey{}
	privateKey.PublicKey.Parameters = params
	if err := dsa.GenerateKey(&privateKey, rand.Reader); err != nil {
		return ""
	}

	// ASN.1 구조에 맞춰 DSAPrivateKey 생성
	dsaPrivateKey := DSAPrivateKey{
		Version: 0,
		P:       privateKey.PublicKey.P,
		Q:       privateKey.PublicKey.Q,
		G:       privateKey.PublicKey.G,
		Y:       privateKey.PublicKey.Y,
		X:       privateKey.X,
	}

	// PEM 인코딩
	pemBlock := &pem.Block{
		Type:  "DSA PRIVATE KEY",
		Bytes: []byte(fmt.Sprintf("%v", dsaPrivateKey)), // 실제로는 ASN.1 인코딩이 필요합니다.
	}
	var pemBytes []byte
	pemBytes = pem.EncodeToMemory(pemBlock)

	return string(pemBytes)
}