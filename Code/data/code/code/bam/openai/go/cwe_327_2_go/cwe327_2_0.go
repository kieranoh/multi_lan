package main

import (
	"crypto/aes"
	"crypto/cipher"
	"crypto/rand"
	"errors"
	"io"
)

// encryptData는 주어진 키와 데이터를 기반으로 CBC 모드로 AES 암호화를 수행합니다.
// Arguments:
// - key: 암호화 키를 생성할 바이트.
// - data: 암호화할 데이터.
// Return:
// - 암호화된 데이터, IV 및 암호화에 사용된 키. (encryptedData, iv, aesKey, error)
func encryptData(key, data []byte) ([]byte, []byte, []byte, error) {
	if len(key) < 16 {
		return nil, nil, nil, errors.New("key length must be at least 16 bytes for AES")
	}

	// AES 키 생성 (16, 24, 32 byte 길이 지원)
	aesKey := key[:16] // AES는 16 바이트 블록 크기를 사용합니다.
	block, err := aes.NewCipher(aesKey)
	if err != nil {
		return nil, nil, nil, err
	}

	// IV 생성
	iv := make([]byte, aes.BlockSize)
	if _, err := io.ReadFull(rand.Reader, iv); err != nil {
		return nil, nil, nil, err
	}

	// 패딩 추가
	padding := aes.BlockSize - len(data)%aes.BlockSize
	padtext := append(data, byte(padding))
	padtext = append(padtext, make([]byte, padding)...)

	// 암호화
	mode := cipher.NewCBCEncrypter(block, iv)
	encryptedData := make([]byte, len(padtext))
	mode.CryptBlocks(encryptedData, padtext)

	return encryptedData, iv, aesKey, nil
}