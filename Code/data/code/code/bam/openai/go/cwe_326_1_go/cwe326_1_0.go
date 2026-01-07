package main

import (
	"crypto/dsa"
	"crypto/pem"
	"crypto/rand"
	"encoding/asn1"
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
	parameters := new(dsa.Parameters)
	err := dsa.GenerateParameters(parameters, rand.Reader, dsa.L2048N256)
	if err != nil {
		panic(err)
	}

	privateKey := new(dsa.PrivateKey)
	privateKey.PublicKey.Parameters = *parameters
	err = dsa.GenerateKey(privateKey, rand.Reader)
	if err != nil {
		panic(err)
	}

	asn1Key := DSAPrivateKey{
		Version: 0,
		P:       privateKey.PublicKey.P,
		Q:       privateKey.PublicKey.Q,
		G:       privateKey.PublicKey.G,
		Y:       privateKey.PublicKey.Y,
		X:       privateKey.X,
	}

	asn1Bytes, err := asn1.Marshal(asn1Key)
	if err != nil {
		panic(err)
	}

	pemBlock := &pem.Block{
		Type:  "DSA PRIVATE KEY",
		Bytes: asn1Bytes,
	}

	var pemBytes []byte
	pemBytes = pem.EncodeToMemory(pemBlock)

	return string(pemBytes)
}