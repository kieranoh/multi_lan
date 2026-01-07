package main

import (
	"crypto/dsa"
	"crypto/rand"
	"crypto/x509"
	"encoding/asn1"
	"encoding/pem"
	"fmt"
	"math/big"
)

// DSAPrivateKeyはDSA秘密鍵のASN.1構造を表します
type DSAPrivateKey struct {
	Version int
	P       *big.Int
	Q       *big.Int
	G       *big.Int
	Y       *big.Int
	X       *big.Int
}

// プライベートDSA鍵を生成し、PEM形式でエクスポートして文字列として返します。
func create_private_key_dsa() string {
	// DSAパラメータを生成
	params := new(dsa.Parameters)
	
	// L=2048, N=256のパラメータを生成（一般的なセキュリティレベル）
	err := dsa.GenerateParameters(params, rand.Reader, dsa.L2048N256)
	if err != nil {
		return ""
	}
	
	// 秘密鍵を生成
	privateKey := new(dsa.PrivateKey)
	privateKey.PublicKey.Parameters = *params
	err = dsa.GenerateKey(privateKey, rand.Reader)
	if err != nil {
		return ""
	}
	
	// DSAPrivateKey構造体を作成
	dsaPrivKey := DSAPrivateKey{
		Version: 0,
		P:       privateKey.P,
		Q:       privateKey.Q,
		G:       privateKey.G,
		Y:       privateKey.Y,
		X:       privateKey.X,
	}
	
	// ASN.1エンコード
	asn1Bytes, err := asn1.Marshal(dsaPrivKey)
	if err != nil {
		return ""
	}
	
	// PEMブロックを作成
	pemBlock := &pem.Block{
		Type:  "DSA PRIVATE KEY",
		Bytes: asn1Bytes,
	}
	
	// PEMエンコード
	pemBytes := pem.EncodeToMemory(pemBlock)
	if pemBytes == nil {
		return ""
	}
	
	return string(pemBytes)
}