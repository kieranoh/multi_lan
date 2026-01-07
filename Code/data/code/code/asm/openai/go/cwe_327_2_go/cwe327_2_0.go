package main

import (
	"crypto/aes"
	"crypto/cipher"
	"crypto/rand"
	"errors"
	"io"
)

// encryptData는 주어진 키와 데이터를 CBC 모드로 암호화합니다.
func encryptData(key, data []byte) ([]byte, []byte, []byte, error) {
	// AES 키 길이는 16, 24, 32 바이트 중 하나여야합니다.
	const aesKeySize = 32 // AES 최대 키 길이
	var aesKey []byte

	if len(key) < aesKeySize {
		return nil, nil, nil, errors.New("key must be at least 32 bytes long for AES")
	}
	aesKey = key[:aesKeySize]

	block, err := aes.NewCipher(aesKey)
	if err != nil {
		return nil, nil, nil, err
	}

	iv := make([]byte, aes.BlockSize)
	if _, err := io.ReadFull(rand.Reader, iv); err != nil {
		return nil, nil, nil, err
	}

	ciphertext := make([]byte, len(data))
	mode := cipher.NewCBCEncrypter(block, iv)
	mode.CryptBlocks(ciphertext, data)

	return ciphertext, iv, aesKey, nil
}