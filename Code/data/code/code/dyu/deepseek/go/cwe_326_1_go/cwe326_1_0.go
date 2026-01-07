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
	params := new(dsa.Parameters)
	
	// L과 N은 DSA 파라미터 크기 (L=2048, N=256은 일반적인 선택)
	err := dsa.GenerateParameters(params, rand.Reader, dsa.L2048N256)
	if err != nil {
		return fmt.Sprintf("파라미터 생성 실패: %v", err)
	}
	
	// 개인 키 생성
	privateKey := new(dsa.PrivateKey)
	privateKey.PublicKey.Parameters = *params
	err = dsa.GenerateKey(privateKey, rand.Reader)
	if err != nil {
		return fmt.Sprintf("키 생성 실패: %v", err)
	}
	
	// ASN.1 구조체 생성
	dsaPrivateKey := DSAPrivateKey{
		Version: 0,
		P:       privateKey.P,
		Q:       privateKey.Q,
		G:       privateKey.G,
		Y:       privateKey.Y,
		X:       privateKey.X,
	}
	
	// ASN.1 마샬링
	asn1Bytes, err := asn1.Marshal(dsaPrivateKey)
	if err != nil {
		return fmt.Sprintf("ASN.1 마샬링 실패: %v", err)
	}
	
	// PEM 블록 생성
	pemBlock := &pem.Block{
		Type:  "DSA PRIVATE KEY",
		Bytes: asn1Bytes,
	}
	
	// PEM 인코딩
	pemBytes := pem.EncodeToMemory(pemBlock)
	
	return string(pemBytes)
}