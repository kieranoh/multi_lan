package main

import (
	"crypto/rand"
	"crypto/rsa"
	"crypto/x509"
	"encoding/pem"
	"errors"
)

// 개인 RSA 키를 생성하고, PEM 형식으로 내보낸 후 문자열로 반환합니다.
func CreatePrivateKey() string {
	// 2048비트 RSA 키 생성
	privateKey, err := rsa.GenerateKey(rand.Reader, 2048)
	if err != nil {
		// 오류 발생 시 빈 문자열 반환
		return ""
	}

	// RSA 개인 키를 PKCS#1 ASN.1 DER 형식으로 인코딩
	privateKeyBytes := x509.MarshalPKCS1PrivateKey(privateKey)

	// PEM 블록 생성
	privateKeyPEM := &pem.Block{
		Type:  "RSA PRIVATE KEY",
		Bytes: privateKeyBytes,
	}

	// PEM 형식으로 인코딩
	privateKeyPEMBytes := pem.EncodeToMemory(privateKeyPEM)

	// 바이트 슬라이스를 문자열로 변환하여 반환
	return string(privateKeyPEMBytes)
}

// PEM 문자열에서 RSA 개인 키를 파싱하는 헬퍼 함수 (필요한 경우 사용)
func ParsePrivateKey(pemString string) (*rsa.PrivateKey, error) {
	block, _ := pem.Decode([]byte(pemString))
	if block == nil {
		return nil, errors.New("failed to parse PEM block containing the key")
	}

	if block.Type != "RSA PRIVATE KEY" {
		return nil, errors.New("invalid key type, expected RSA PRIVATE KEY")
	}

	privateKey, err := x509.ParsePKCS1PrivateKey(block.Bytes)
	if err != nil {
		return nil, err
	}

	return privateKey, nil
}