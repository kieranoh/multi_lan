package main

import (
	"crypto/rand"
	"crypto/rsa"
	"encoding/pem"
	"fmt"
	"log"
)

// CreatePrivateKey는 개인 RSA 키를 생성하고, PEM 형식으로 내보낸 후 문자열로 반환합니다.
func CreatePrivateKey() string {
	// 2048 비트 RSA 키 생성
	privKey, err := rsa.GenerateKey(rand.Reader, 2048)
	if err != nil {
		log.Fatalf("키 생성 오류: %v", err)
	}

	// 개인 키를 PEM 형식으로 변환
	privKeyBytes := x509.MarshalPKCS8PrivateKey(privKey)
	pemBlock := &pem.Block{
		Type:  "PRIVATE KEY",
		Bytes: privKeyBytes,
	}

	// PEM 블록을 문자열로 변환
	var pemData bytes.Buffer
	if err := pem.Encode(&pemData, pemBlock); err != nil {
		log.Fatalf("PEM 인코딩 오류: %v", err)
	}

	return pemData.String()
}

func main() {
	// 개인 키 생성 및 출력
	privateKey := CreatePrivateKey()
	fmt.Println(privateKey)
}