package main

import (
	"crypto/sha256"
	"encoding/hex"
	"fmt"
)

// hashCertificate 安全地对给定证书进行哈希，并将哈希作为十六进制字符串返回。
// @param cert 要进行哈希的证书。
// @return 安全哈希的证书，作为十六进制字符串。
func hashCertificate(cert string) string {
	hash := sha256.New()
	hash.Write([]byte(cert))
	return hex.EncodeToString(hash.Sum(nil))
}