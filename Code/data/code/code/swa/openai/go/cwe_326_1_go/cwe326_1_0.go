package main

import (
	"crypto/dsa"
	"crypto/x509"
	"encoding/pem"
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

// create_private_key_dsa는 개인 DSA 키를 생성하고, PEM 형식을 사용하여 내보낸 다음, 문자열로 반환합니다.
func create_private_key_dsa() string {
	params := dsa.Parameters{}
	_ = dsa.GenerateParameters(&params, nil) // 오류 처시는 burada ele alınmalıdır

	privateKey := new(dsa.PrivateKey)
	_ = dsa.GenerateKey(privateKey, nil) // 오류 처isini burada ele alınmalıdır

	// DSA özel anahtarını PEM formatında kodlayın
	privASN1 := privateKey.X
	pemBlock := &pem.Block{
		Type:  "DSA PRIVATE KEY",
		Bytes: x509.MarshalPKCS8PrivateKey(privateKey),
	}

	var pemData []byte
	pemData = pem.EncodeToMemory(pemBlock)

	return string(pemData)
}