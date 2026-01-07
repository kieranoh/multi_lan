package main

import (
	"crypto/dsa"
	"crypto/rand"
	"encoding/asn1"
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
	// DSA 파라미터 생성
	var params dsa.Parameters
	// L=2048, N=256 (권장 파라미터)
	if err := dsa.GenerateParameters(&params, rand.Reader, dsa.L2048N256); err != nil {
		return fmt.Sprintf("파라미터 생성 실패: %v", err)
	}

	// 개인 키 생성
	var privateKey dsa.PrivateKey
	privateKey.Parameters = params
	if err := dsa.GenerateKey(&privateKey, rand.Reader); err != nil {
		return fmt.Sprintf("개인 키 생성 실패: %v", err)
	}

	// DSAPrivateKey 구조체 채우기
	dsaPrivKey := DSAPrivateKey{
		Version: 0,
		P:       privateKey.P,
		Q:       privateKey.Q,
		G:       privateKey.G,
		Y:       privateKey.Y,
		X:       privateKey.X,
	}

	// ASN.1 DER 인코딩
	derBytes, err := asn1.Marshal(dsaPrivKey)
	if err != nil {
		return fmt.Sprintf("ASN.1 마샬링 실패: %v", err)
	}

	// PEM 블록 생성
	pemBlock := &pem.Block{
		Type:  "DSA PRIVATE KEY",
		Bytes: derBytes,
	}

	// PEM 형식으로 인코딩
	pemBytes := pem.EncodeToMemory(pemBlock)
	if pemBytes == nil {
		return "PEM 인코딩 실패"
	}

	return string(pemBytes)
}