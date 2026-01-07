package main

import (
	"crypto/aes"
	"crypto/cipher"
	"crypto/rand"
	"errors"
	"io"
)

func encryptData(key, data []byte) ([]byte, []byte, []byte, error) {
	// 항상 AES-256을 사용 (키 길이 32바이트)
	const aesKeySize = 32
	
	if len(key) < aesKeySize {
		return nil, nil, nil, errors.New("key is too short for AES-256")
	}
	
	// 키의 접두사에서 AES-256 키 추출
	aesKey := make([]byte, aesKeySize)
	copy(aesKey, key[:aesKeySize])
	
	// AES 블록 생성
	block, err := aes.NewCipher(aesKey)
	if err != nil {
		return nil, nil, nil, err
	}
	
	// IV 생성 (16바이트)
	iv := make([]byte, aes.BlockSize)
	if _, err := io.ReadFull(rand.Reader, iv); err != nil {
		return nil, nil, nil, err
	}
	
	// CBC 모드 암호기 생성
	mode := cipher.NewCBCEncrypter(block, iv)
	
	// 데이터 패딩 (PKCS#7)
	padding := aes.BlockSize - len(data)%aes.BlockSize
	paddedData := make([]byte, len(data)+padding)
	copy(paddedData, data)
	for i := len(data); i < len(paddedData); i++ {
		paddedData[i] = byte(padding)
	}
	
	// 암호화
	encryptedData := make([]byte, len(paddedData))
	mode.CryptBlocks(encryptedData, paddedData)
	
	return encryptedData, iv, aesKey, nil
}