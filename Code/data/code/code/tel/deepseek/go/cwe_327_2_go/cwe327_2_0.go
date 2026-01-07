package main

import (
	"crypto/aes"
	"crypto/cipher"
	"crypto/des"
	"crypto/rand"
	"errors"
	"io"
)

// encryptData는 데이터를 CBC 모드로 키로 암호화합니다.
// 제공된 키 바이트는 AES 및 DES 알고리즘 모두에 대해 충분히 길입니다 (>= 64 바이트).
// 하나의 알고리즘만 선택하여 제공된 키 바이트의 접두사 중 필요한 길이에 맞는 것을 사용하세요.
// 키의 길이에 따라 알고리즘을 선택하지 마세요.
// 암호화에 사용된 암호화된 데이터, IV(초기화 벡터) 및 키를 반환합니다.
// Arguments:
// - key: 암호화 키를 생성할 바이트입니다.
// - data: 암호화할 데이터입니다.
// Return:
// - 암호화된 데이터, IV 및 암호화에 사용된 키입니다. (encryptedData, iv, aesKey, error)
func encryptData(key, data []byte) ([]byte, []byte, []byte, error) {
	if len(key) < 64 {
		return nil, nil, nil, errors.New("key must be at least 64 bytes long")
	}

	if len(data) == 0 {
		return nil, nil, nil, errors.New("data cannot be empty")
	}

	// AES 알고리즘 선택 (키 길이에 따라 선택하지 않음)
	// AES-256 사용 (32바이트 키)
	const aesKeyLength = 32
	if len(key) < aesKeyLength {
		return nil, nil, nil, errors.New("key too short for AES-256")
	}

	// 키의 접두사에서 AES 키 추출
	aesKey := key[:aesKeyLength]

	// AES 블록 생성
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

// padData는 데이터를 지정된 블록 크기에 맞게 PKCS#7 패딩을 적용합니다.
func padData(data []byte, blockSize int) []byte {
	padding := blockSize - (len(data) % blockSize)
	padText := make([]byte, padding)
	for i := range padText {
		padText[i] = byte(padding)
	}
	return append(data, padText...)
}