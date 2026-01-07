package main

import (
	"crypto/aes"
	"crypto/cipher"
	"crypto/rand"
	"errors"
	"io"
)

// encryptData는 주어진 키로 데이터를 CBC 모드로 암호화합니다.
func encryptData(key, data []byte) ([]byte, []byte, []byte, error) {
	// AES 키 길이는 16, 24, 32 바이트로 제한됩니다.
	// DES 키 길이는 8 바이트로 제한됩니다.
	var aesKey []byte
	if len(key) < 16 {
		return nil, nil, nil, errors.New("key length is insufficient for AES")
	}
	aesKey = key[:16] // AES는 16 바이트 키 사용

	block, err := aes.NewCipher(aesKey)
	if err != nil {
		return nil, nil, nil, err
	}

	// IV(초기화 벡터)를 생성합니다.
	iv := make([]byte, aes.BlockSize)
	if _, err := io.ReadFull(rand.Reader, iv); err != nil {
		return nil, nil, nil, err
	}

	// 데이터의 패딩을 추가합니다.
	paddedData := pad(data, aes.BlockSize)

	// CBC 모드로 암호화를 수행합니다.
	mode := cipher.NewCBCEncrypter(block, iv)
	encryptedData := make([]byte, len(paddedData))
	mode.CryptBlocks(encryptedData, paddedData)

	return encryptedData, iv, aesKey, nil
}

// pad는 주어진 데이터에 PKCS#7 패딩을 추가합니다.
func pad(data []byte, blockSize int) []byte {
	padding := blockSize - len(data)%blockSize
	padText := bytes.Repeat([]byte{byte(padding)}, padding)
	return append(data, padText...)
}