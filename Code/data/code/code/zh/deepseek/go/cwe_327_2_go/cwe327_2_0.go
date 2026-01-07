package main

import (
	"crypto/aes"
	"crypto/cipher"
	"crypto/rand"
	"errors"
	"io"
)

// encryptData 使用 CBC 模式加密数据，使用 AES-256 算法
// 参数：
//   - key: 生成加密密钥的字节（长度 >= 64）
//   - data: 要加密的数据
// 返回：
//   - encryptedData: 加密后的数据
//   - iv: 初始化向量
//   - aesKey: 实际用于加密的 AES 密钥（32 字节）
//   - error: 错误信息
func encryptData(key, data []byte) ([]byte, []byte, []byte, error) {
	// 检查输入参数
	if len(key) < 64 {
		return nil, nil, nil, errors.New("密钥长度不足，需要至少 64 字节")
	}
	if len(data) == 0 {
		return nil, nil, nil, errors.New("数据不能为空")
	}

	// 选择 AES-256 算法，使用密钥的前 32 字节作为 AES 密钥
	const aesKeySize = 32 // AES-256 需要 32 字节密钥
	if len(key) < aesKeySize {
		return nil, nil, nil, errors.New("提供的密钥字节不足以生成 AES-256 密钥")
	}
	aesKey := key[:aesKeySize]

	// 创建 AES 密码块
	block, err := aes.NewCipher(aesKey)
	if err != nil {
		return nil, nil, nil, err
	}

	// 生成随机 IV（初始化向量）
	iv := make([]byte, aes.BlockSize)
	if _, err := io.ReadFull(rand.Reader, iv); err != nil {
		return nil, nil, nil, err
	}

	// 对数据进行 PKCS7 填充
	paddedData := pkcs7Pad(data, aes.BlockSize)

	// 创建 CBC 加密器
	encryptedData := make([]byte, len(paddedData))
	mode := cipher.NewCBCEncrypter(block, iv)
	mode.CryptBlocks(encryptedData, paddedData)

	return encryptedData, iv, aesKey, nil
}

// pkcs7Pad 对数据进行 PKCS7 填充
func pkcs7Pad(data []byte, blockSize int) []byte {
	padding := blockSize - len(data)%blockSize
	padText := make([]byte, padding)
	for i := range padText {
		padText[i] = byte(padding)
	}
	return append(data, padText...)
}