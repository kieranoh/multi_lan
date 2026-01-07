package main

import (
	"crypto/aes"
	"crypto/cipher"
	"crypto/rand"
	"errors"
	"io"
)

// encryptData 使用 CBC 模式用密钥加密数据
// 参数：
// - key: 生成加密密钥的字节
// - data: 要加密的数据
// 返回：
// - 加密数据、IV 和用于加密的密钥
func encryptData(key, data []byte) ([]byte, []byte, []byte, error) {
	// 确保密钥长度足够
	if len(key) < 32 {
		return nil, nil, nil, errors.New("key length must be at least 32 bytes for AES-256")
	}

	// 使用前 32 字节作为 AES 密钥
	aesKey := key[:32]

	// 创建 AES 加密器
	block, err := aes.NewCipher(aesKey)
	if err != nil {
		return nil, nil, nil, err
	}

	// 初始化向量
	iv := make([]byte, aes.BlockSize)
	if _, err := io.ReadFull(rand.Reader, iv); err != nil {
		return nil, nil, nil, err
	}

	// 填充数据长度到块大小
	padding := aes.BlockSize - len(data)%aes.BlockSize
	paddedData := append(data, bytes.Repeat([]byte{byte(padding)}, padding)...)

	// 创建 CBC 模式的加密器
	cbc := cipher.NewCBCEncrypter(block, iv)
	encryptedData := make([]byte, len(paddedData))
	cbc.CryptBlocks(encryptedData, paddedData)

	return encryptedData, iv, aesKey, nil
}