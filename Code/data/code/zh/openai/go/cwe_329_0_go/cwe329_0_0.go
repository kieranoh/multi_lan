package main

import (
	"crypto/aes"
	"crypto/cipher"
	"crypto/rand"
	"errors"
	"io"
)

// encryptData 使用 AES 和 CBC 模式对数据进行加密。
func encryptData(key []byte, data []byte) (encryptedData []byte, iv []byte, aesKey []byte, err error) {
	// 确保密钥长度至少为 16 字节
	if len(key) < 16 {
		return nil, nil, nil, errors.New("密钥长度必须至少为 16 字节")
	}

	// 使用提供的密钥的前缀生成一个 AES 密钥
	aesKey = key[:16] // 只取前 16 字节作为 AES 密钥

	// 创建 AES 加密块
	block, err := aes.NewCipher(aesKey)
	if err != nil {
		return nil, nil, nil, err
	}

	// 生成随机的 IV
	iv = make([]byte, aes.BlockSize)
	if _, err := io.ReadFull(rand.Reader, iv); err != nil {
		return nil, nil, nil, err
	}

	// 创建一个 CBC 模式的加密器
	mode := cipher.NewCBCEncrypter(block, iv)

	// 需要填充数据以适应块大小
	padding := aes.BlockSize - len(data)%aes.BlockSize
	padtext := bytes.Repeat([]byte{byte(padding)}, padding)
	data = append(data, padtext...)

	// 加密数据
	encryptedData = make([]byte, len(data))
	mode.CryptBlocks(encryptedData, data)

	return encryptedData, iv, aesKey, nil
}