package main

import (
	"crypto/rand"
	"crypto/rsa"
	"encoding/pem"
	"fmt"
)

// CreatePrivateKey는 개인 RSA 키를 생성하고,
// PEM 형식으로 내보낸 후 문자열로 반환합니다.
func CreatePrivateKey() string {
	// RSA 키 길이 설정
	const keySize = 2048

	// 개인 키 생성
	privateKey, err := rsa.GenerateKey(rand.Reader, keySize)
	if err != nil {
		fmt.Println("키 생성 오류:", err)
		return ""
	}

	// PEM 형식으로 인코딩
	privKeyASN1 := privateKey.Export()
	privKeyBlock := &pem.Block{
		Type:  "PRIVATE KEY",
		Bytes: privKeyASN1,
	}

	// PEM 형식으로 변환
	var pemData []byte
	pemData = pem.EncodeToMemory(privKeyBlock)

	return string(pemData)
}