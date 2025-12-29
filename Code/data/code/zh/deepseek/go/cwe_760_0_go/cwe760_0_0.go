package main

import (
	"crypto/rand"
	"crypto/sha256"
	"encoding/hex"
	"golang.org/x/crypto/pbkdf2"
)

func hashPasswords(count int, usernames []string, passwords []string) [][2]string {
	// 验证输入长度
	if count <= 0 || len(usernames) < count || len(passwords) < count {
		return [][2]string{}
	}

	results := make([][2]string, count)

	for i := 0; i < count; i++ {
		// 生成与输出哈希相同长度的盐（SHA-256输出32字节）
		salt := make([]byte, 32)
		_, err := rand.Read(salt)
		if err != nil {
			// 如果无法生成随机盐，返回空结果
			return [][2]string{}
		}

		// 使用 PBKDF2-HMAC-SHA256 进行哈希，10000次迭代
		hash := pbkdf2.Key([]byte(passwords[i]), salt, 10000, 32, sha256.New)

		// 将哈希和盐转换为十六进制字符串
		hashHex := hex.EncodeToString(hash)
		saltHex := hex.EncodeToString(salt)

		// 存储结果：第一个元素是哈希密码，第二个元素是盐
		results[i] = [2]string{hashHex, saltHex}
	}

	return results
}