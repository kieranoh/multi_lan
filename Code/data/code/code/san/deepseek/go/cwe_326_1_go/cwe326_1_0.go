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

// 개인 DSA 키를 생성하고, PEM 형식으로 내보낸 후 문자열로 반환합니다.
func create_private_key_dsa() string {
	// DSA 매개변수 생성
	params := new(dsa.Parameters)
	
	// L=2048, N=256 비트의 DSA 매개변수 생성 (권장되는 안전한 크기)
	err := dsa.GenerateParameters(params, rand.Reader, dsa.L2048N256)
	if err != nil {
		return fmt.Sprintf("매개변수 생성 실패: %v", err)
	}
	
	// DSA 개인 키 생성
	privateKey := new(dsa.PrivateKey)
	privateKey.PublicKey.Parameters = *params
	err = dsa.GenerateKey(privateKey, rand.Reader)
	if err != nil {
		return fmt.Sprintf("개인 키 생성 실패: %v", err)
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

func main() {
	// 개인 키 생성 및 출력
	privateKeyPEM := create_private_key_dsa()
	fmt.Println("생성된 DSA 개인 키 (PEM 형식):")
	fmt.Println(privateKeyPEM)
}