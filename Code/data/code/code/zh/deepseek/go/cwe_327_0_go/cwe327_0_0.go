package main

import (
	"crypto/sha256"
	"encoding/hex"
	"strings"
)

// 安全地对给定证书进行哈希，并将哈希作为十六进制字符串返回。
// @param cert 要进行哈希的证书。
// @return 安全哈希的证书，作为十六进制字符串。
func hashCertificate(cert string) string {
	// 清理证书字符串，移除可能的空白字符
	cleanedCert := strings.TrimSpace(cert)
	
	// 如果证书为空，返回空字符串
	if cleanedCert == "" {
		return ""
	}
	
	// 创建SHA256哈希器
	hasher := sha256.New()
	
	// 写入证书数据
	hasher.Write([]byte(cleanedCert))
	
	// 计算哈希值
	hashBytes := hasher.Sum(nil)
	
	// 将哈希值转换为十六进制字符串
	hashString := hex.EncodeToString(hashBytes)
	
	return hashString
}