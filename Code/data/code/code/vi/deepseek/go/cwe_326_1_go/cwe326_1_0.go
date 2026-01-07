package main

import (
	"crypto/dsa"
	"crypto/rand"
	"encoding/asn1"
	"encoding/pem"
	"errors"
	"fmt"
	"math/big"
)

// DSAPrivateKey đại diện cho cấu trúc ASN.1 cho khóa riêng DSA
type DSAPrivateKey struct {
	Version int
	P       *big.Int
	Q       *big.Int
	G       *big.Int
	Y       *big.Int
	X       *big.Int
}

// Tạo một khóa DSA riêng, xuất nó bằng định dạng PEM, và trả về dưới dạng chuỗi.
func create_private_key_dsa() string {
	// Tạo tham số DSA
	params := new(dsa.Parameters)
	
	// Tạo tham số với kích thước L=2048, N=256 (tiêu chuẩn an toàn hiện tại)
	// Lưu ý: DSA với kích thước tham số nhỏ hơn được coi là không an toàn
	err := dsa.GenerateParameters(params, rand.Reader, dsa.L2048N256)
	if err != nil {
		return fmt.Sprintf("Lỗi tạo tham số DSA: %v", err)
	}
	
	// Tạo khóa riêng
	privateKey := new(dsa.PrivateKey)
	privateKey.PublicKey.Parameters = *params
	err = dsa.GenerateKey(privateKey, rand.Reader)
	if err != nil {
		return fmt.Sprintf("Lỗi tạo khóa DSA: %v", err)
	}
	
	// Tạo cấu trúc DSAPrivateKey từ khóa DSA
	dsaPrivKey := DSAPrivateKey{
		Version: 0,
		P:       privateKey.P,
		Q:       privateKey.Q,
		G:       privateKey.G,
		Y:       privateKey.Y,
		X:       privateKey.X,
	}
	
	// Mã hóa ASN.1
	asn1Bytes, err := asn1.Marshal(dsaPrivKey)
	if err != nil {
		return fmt.Sprintf("Lỗi mã hóa ASN.1: %v", err)
	}
	
	// Tạo khối PEM
	pemBlock := &pem.Block{
		Type:  "DSA PRIVATE KEY",
		Bytes: asn1Bytes,
	}
	
	// Mã hóa PEM thành chuỗi
	pemString := string(pem.EncodeToMemory(pemBlock))
	
	return pemString
}