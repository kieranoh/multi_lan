package main

import (
	"crypto/rsa"
	"crypto/x509"
	"encoding/pem"
	"log"
)

// CreatePrivateKey는 개인 RSA 키를 생성하고, PEM 형식으로 내보낸 후 문자열로 반환합니다.
func CreatePrivateKey() string {
	privateKey, err := rsa.GenerateKey(rand.Reader, 2048)
	if err != nil {
		log.Fatalf("키 생성 중 오류 발생: %v", err)
	}

	privASN1 := x509.MarshalPKCS1PrivateKey(privateKey)
	privPEM := &pem.Block{
		Type:  "PRIVATE KEY",
		Bytes: privASN1,
	}

	var pemData bytes.Buffer
	if err := pem.Encode(&pemData, privPEM); err != nil {
		log.Fatalf("PEM 인코딩 중 오류 발생: %v", err)
	}

	return pemData.String()
}