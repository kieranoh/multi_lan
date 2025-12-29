package main

import (
	"crypto/rand"
	"crypto/rsa"
	"crypto/x509"
	"encoding/pem"
	"errors"
)

// CreatePrivateKey 生成一个私有 RSA 密钥，使用 PEM 格式导出，并将其作为字符串返回。
func CreatePrivateKey() string {
	// 生成 RSA 私钥
	privateKey, err := rsa.GenerateKey(rand.Reader, 2048)
	if err != nil {
		// 在实际应用中，可能需要更复杂的错误处理
		// 这里返回空字符串表示生成失败
		return ""
	}

	// 将私钥转换为 PKCS#1 DER 编码
	privateKeyDER := x509.MarshalPKCS1PrivateKey(privateKey)

	// 创建 PEM 块
	privateKeyBlock := &pem.Block{
		Type:  "RSA PRIVATE KEY",
		Bytes: privateKeyDER,
	}

	// 将 PEM 块编码为字符串
	privateKeyPEM := pem.EncodeToMemory(privateKeyBlock)

	return string(privateKeyPEM)
}