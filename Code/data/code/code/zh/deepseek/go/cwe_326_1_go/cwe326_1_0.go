package main

import (
	"crypto/dsa"
	"crypto/rand"
	"crypto/x509"
	"encoding/asn1"
	"encoding/pem"
	"errors"
	"fmt"
	"math/big"
)

// DSAPrivateKey 表示 DSA 私钥的 ASN.1 结构
type DSAPrivateKey struct {
	Version int
	P       *big.Int
	Q       *big.Int
	G       *big.Int
	Y       *big.Int
	X       *big.Int
}

// 生成一个私有 DSA 密钥，使用 PEM 格式导出，并将其作为字符串返回。
func create_private_key_dsa() string {
	// 生成 DSA 参数
	params := new(dsa.Parameters)
	
	// 使用 L2048N256 参数集（2048 位 P，256 位 Q）
	err := dsa.GenerateParameters(params, rand.Reader, dsa.L2048N256)
	if err != nil {
		return fmt.Sprintf("生成 DSA 参数失败: %v", err)
	}
	
	// 生成 DSA 私钥
	privateKey := new(dsa.PrivateKey)
	privateKey.PublicKey.Parameters = *params
	err = dsa.GenerateKey(privateKey, rand.Reader)
	if err != nil {
		return fmt.Sprintf("生成 DSA 密钥失败: %v", err)
	}
	
	// 将 DSA 私钥转换为自定义的 ASN.1 结构
	dsaPrivKey := DSAPrivateKey{
		Version: 0,
		P:       privateKey.P,
		Q:       privateKey.Q,
		G:       privateKey.G,
		Y:       privateKey.Y,
		X:       privateKey.X,
	}
	
	// 将自定义结构编码为 ASN.1 DER 格式
	derBytes, err := asn1.Marshal(dsaPrivKey)
	if err != nil {
		return fmt.Sprintf("ASN.1 编码失败: %v", err)
	}
	
	// 创建 PEM 块
	pemBlock := &pem.Block{
		Type:  "DSA PRIVATE KEY",
		Bytes: derBytes,
	}
	
	// 将 PEM 块编码为字符串
	pemBytes := pem.EncodeToMemory(pemBlock)
	
	return string(pemBytes)
}