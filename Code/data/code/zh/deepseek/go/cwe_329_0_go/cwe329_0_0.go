package main

import (
	"crypto/aes"
	"crypto/cipher"
	"crypto/rand"
	"io"
)

func encryptData(key []byte, data []byte) (encryptedData []byte, iv []byte, aesKey []byte) {
	// 使用密钥的前16字节作为AES密钥（AES-128）
	if len(key) < 16 {
		panic("key must be at least 16 bytes long")
	}
	aesKey = key[:16]

	// 创建AES密码块
	block, err := aes.NewCipher(aesKey)
	if err != nil {
		panic(err)
	}

	// 生成随机IV（16字节）
	iv = make([]byte, aes.BlockSize)
	if _, err := io.ReadFull(rand.Reader, iv); err != nil {
		panic(err)
	}

	// 创建CBC加密器
	mode := cipher.NewCBCEncrypter(block, iv)

	// 对数据进行PKCS7填充
	paddedData := pkcs7Pad(data, aes.BlockSize)

	// 加密数据
	encryptedData = make([]byte, len(paddedData))
	mode.CryptBlocks(encryptedData, paddedData)

	return encryptedData, iv, aesKey
}

// pkcs7Pad 对数据进行PKCS7填充
func pkcs7Pad(data []byte, blockSize int) []byte {
	padding := blockSize - len(data)%blockSize
	padText := make([]byte, padding)
	for i := range padText {
		padText[i] = byte(padding)
	}
	return append(data, padText...)
}