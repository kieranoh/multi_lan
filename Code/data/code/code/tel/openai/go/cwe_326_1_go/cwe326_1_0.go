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
	params := new(dsa.Parameters)
	err := dsa.GenerateParameters(params, rand.Reader, dsa.L2048N256)
	if err != nil {
		fmt.Println("Error generating parameters:", err)
		return ""
	}

	privateKey := new(dsa.PrivateKey)
	privateKey.PublicKey.Parameters = *params
	err = dsa.GenerateKey(privateKey, rand.Reader)
	if err != nil {
		fmt.Println("Error generating key:", err)
		return ""
	}

	dsaKey := DSAPrivateKey{
		Version: 0,
		P:       privateKey.PublicKey.P,
		Q:       privateKey.PublicKey.Q,
		G:       privateKey.PublicKey.G,
		Y:       privateKey.PublicKey.Y,
		X:       privateKey.X,
	}

	// PEM 인코딩
	privKeyBytes, err := x509.MarshalPKCS8PrivateKey(privateKey)
	if err != nil {
		fmt.Println("Error marshaling private key:", err)
		return ""
	}

	var pemKey bytes.Buffer
	err = pem.Encode(&pemKey, &pem.Block{Type: "PRIVATE KEY", Bytes: privKeyBytes})
	if err != nil {
		fmt.Println("Error encoding PEM:", err)
		return ""
	}

	return pemKey.String()
}