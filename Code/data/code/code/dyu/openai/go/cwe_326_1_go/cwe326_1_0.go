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

// 개인 DSA 키를 생성하고, PEM 형식을 사용하여 내보낸 다음, 문자열로 반환합니다.
func create_private_key_dsa() string {
	priv := new(dsa.PrivateKey)
	params := new(dsa.Parameters)
	if err := dsa.GenerateParameters(params, rand.Reader, dsa.L2048N256); err != nil {
		return ""
	}
	if err := priv.GenerateKey(params, rand.Reader); err != nil {
		return ""
	}

	// PEM 인코딩을 위한 버퍼
	privASN1 := &DSAPrivateKey{
		Version: 0,
		P:       priv.PublicKey.P,
		Q:       priv.PublicKey.Q,
		G:       priv.PublicKey.G,
		Y:       priv.PublicKey.Y,
		X:       priv.X,
	}

	privBytes, err := asn1.Marshal(privASN1)
	if err != nil {
		return ""
	}

	// PEM 블록 생성
	var pemBlock = &pem.Block{
		Type:  "DSA PRIVATE KEY",
		Bytes: privBytes,
	}

	var pemBuffer bytes.Buffer
	if err := pem.Encode(&pemBuffer, pemBlock); err != nil {
		return ""
	}

	return pemBuffer.String()
}