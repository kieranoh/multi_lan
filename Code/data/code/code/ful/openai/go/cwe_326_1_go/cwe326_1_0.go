package main

import (
	"crypto/dsa"
	"crypto/pem"
	"encoding/asn1"
	"math/big"
	"strings"
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
	privKey := new(dsa.PrivateKey)
	params := new(dsa.Parameters)
	dsa.GenerateParameters(params, dsa.L1024N160) // 파라미터 설정
	privKey.GenerateKey(params)

	// ASN.1 인코딩을 위한 DSAPrivateKey 구조체 설정
	dsaPrivateKey := DSAPrivateKey{
		Version: 0,
		P:       privKey.PublicKey.P,
		Q:       privKey.PublicKey.Q,
		G:       privKey.PublicKey.G,
		Y:       privKey.PublicKey.Y,
		X:       privKey.X,
	}

	// ASN.1 인코딩
	encoded, err := asn1.Marshal(dsaPrivateKey)
	if err != nil {
		return ""
	}

	// PEM 인코딩
	var sb strings.Builder
	block := &pem.Block{
		Type:  "DSA PRIVATE KEY",
		Bytes: encoded,
	}
	if err := pem.Encode(&sb, block); err != nil {
		return ""
	}

	return sb.String()
}