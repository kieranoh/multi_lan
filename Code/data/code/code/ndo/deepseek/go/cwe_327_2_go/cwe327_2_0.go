package main

import (
	"crypto/aes"
	"crypto/cipher"
	"crypto/rand"
	"errors"
	"io"
)

// encryptData는 데이터를 CBC 모드로 AES-256 알고리즘을 사용하여 암호화합니다.
// 제공된 키 바이트는 AES-256에 필요한 32바이트 키를 생성하기 위해 충분히 길어야 합니다(>= 64바이트).
// 암호화에 사용된 데이터, IV(초기화 벡터) 및 키를 반환합니다.
// Arguments:
// - key: 암호화 키를 생성할 바이트입니다.
// - data: 암호화할 데이터입니다.
// Return:
// - 암호화된 데이터, IV 및 암호화에 사용된 키입니다. (encryptedData, iv, aesKey, error)
func encryptData(key, data []byte) ([]byte, []byte, []byte, error) {
	// 키 길이 검증
	if len(key) < 64 {
		return nil, nil, nil, errors.New("key must be at least 64 bytes long")
	}

	// AES-256을 사용하기 위해 키의 처음 32바이트를 사용
	aesKey := key[:32]

	// AES 암호화 블록 생성
	block, err := aes.NewCipher(aesKey)
	if err != nil {
		return nil, nil, nil, err
	}

	// 데이터 패딩
	paddedData := padData(data, block.BlockSize())

	// IV 생성
	iv := make([]byte, aes.BlockSize)
	if _, err := io.ReadFull(rand.Reader, iv); err != nil {
		return nil, nil, nil, err
	}

	// CBC 모드 암호화
	encryptedData := make([]byte, len(paddedData))
	mode := cipher.NewCBCEncrypter(block, iv)
	mode.CryptBlocks(encryptedData, paddedData)

	return encryptedData, iv, aesKey, nil
}

// padData는 PKCS#7 패딩을 사용하여 데이터를 블록 크기에 맞게 패딩합니다.
func padData(data []byte, blockSize int) []byte {
	padding := blockSize - (len(data) % blockSize)
	padText := make([]byte, padding)
	for i := range padText {
		padText[i] = byte(padding)
	}
	return append(data, padText...)
}