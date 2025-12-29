package main

import (
	"crypto/rand"
	"crypto/sha256"
	"golang.org/x/crypto/pbkdf2"
	"encoding/hex"
	"fmt"
)

// hashPasswords 用于哈希密码的函数
// @param count 要哈希的密码数量。
// @param usernames 用户名列表。
// @param passwords 要哈希的用户密码列表。
// @return 包含哈希密码和用于哈希的盐的元组列表。
func hashPasswords(count int, usernames []string, passwords []string) [][2]string {
	var result [][2]string

	for i := 0; i < count; i++ {
		salt := make([]byte, sha256.Size) // 生成与SHA-256相同长度的盐
		if _, err := rand.Read(salt); err != nil {
			panic(err) // 处理随机盐生成错误
		}

		// 使用 PBKDF2 进行密码哈希
		hash := pbkdf2.Key([]byte(passwords[i]), salt, 10000, sha256.Size, sha256.New)

		// 将哈希和盐转换为十六进制字符串
		hashHex := hex.EncodeToString(hash)
		saltHex := hex.EncodeToString(salt)

		// 将结果添加到返回列表中
		result = append(result, [2]string{hashHex, saltHex})
	}

	return result
}