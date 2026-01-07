package main

import (
	"crypto/aes"
	"crypto/cipher"
	"crypto/rand"
	"errors"
	"io"
)

// encryptData는 주어진 키 바이트를 사용하여 데이터를 CBC 모드로 암호화합니다.
func encryptData(key, data []byte) ([]byte, []byte, []byte, error) {
	// AES의 키 길이는 16(128 비트), 24(192 비트), 또는 32(256 비트) 바이트여야 합니다.
	// 제공된 키 바이트가 64 바이트 이상이라고 가정하므로, 32 바이트를 초과하는 부분은 무시합니다.
	var aesKey []byte
	if len(key) >= 32 {
		aesKey = key[:32] // 256비트 키
	} else if len(key) >= 24 {
		aesKey = key[:24] // 192비트 키
	} else if len(key) >= 16 {
		aesKey = key[:16] // 128비트 키
	} else {
		return nil, nil, nil, errors.New("키가 너무 짧습니다")
	}

	// IV(초기화 벡터)를 생성합니다.
	iv := make([]byte, aes.BlockSize)
	if _, err := io.ReadFull(rand.Reader, iv); err != nil {
		return nil, nil, nil, err
	}

	// AES 암호화 블록을 초기화합니다.
	block, err := aes.NewCipher(aesKey)
	if err != nil {
		return nil, nil, nil, err
	}

	// 데이터의 패딩을 처리합니다.
	padding := aes.BlockSize - len(data)%aes.BlockSize
	padtext := append(data, bytes.Repeat([]byte{byte(padding)}, padding)...)

	// CBC 모드로 암호화합니다.
	mode := cipher.NewCBCEncrypter(block, iv)
	encryptedData := make([]byte, len(padtext))
	mode.CryptBlocks(encryptedData, padtext)

	return encryptedData, iv, aesKey, nil
}