package main

import (
	"crypto/dsa"
	"crypto/rand"
	"crypto/x509"
	"encoding/asn1"
	"encoding/pem"
	"errors"
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
	// DSA 매개변수 생성
	params := &dsa.Parameters{}
	
	// L=2048, N=256 비트의 DSA 매개변수 생성 (FIPS 186-3)
	err := dsa.GenerateParameters(params, rand.Reader, dsa.L2048N256)
	if err != nil {
		return fmt.Sprintf("매개변수 생성 실패: %v", err)
	}

	// 개인 키 생성
	privateKey := &dsa.PrivateKey{
		PublicKey: dsa.PublicKey{
			Parameters: *params,
		},
	}
	
	err = dsa.GenerateKey(privateKey, rand.Reader)
	if err != nil {
		return fmt.Sprintf("키 생성 실패: %v", err)
	}

	// ASN.1 형식으로 마샬링
	dsaPrivateKey := DSAPrivateKey{
		Version: 0,
		P:       privateKey.P,
		Q:       privateKey.Q,
		G:       privateKey.G,
		Y:       privateKey.Y,
		X:       privateKey.X,
	}

	asn1Bytes, err := asn1.Marshal(dsaPrivateKey)
	if err != nil {
		return fmt.Sprintf("ASN.1 마샬링 실패: %v", err)
	}

	// PEM 블록 생성
	pemBlock := &pem.Block{
		Type:  "DSA PRIVATE KEY",
		Bytes: asn1Bytes,
	}

	// PEM 형식으로 인코딩
	pemBytes := pem.EncodeToMemory(pemBlock)
	if pemBytes == nil {
		return "PEM 인코딩 실패"
	}

	return string(pemBytes)
}