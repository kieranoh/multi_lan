package main

import (
	"crypto/aes"
	"crypto/cipher"
	"crypto/rand"
	"errors"
	"io"
)

// encryptData는 데이터를 CBC 모드로 AES 알고리즘을 사용하여 암호화합니다.
// 제공된 키 바이트는 AES 및 DES 알고리즘 모두에 대해 충분히 길지만(>= 64 바이트),
// AES 알고리즘만 구현하고 AES-256에 필요한 32바이트 접두사를 사용합니다.
// 암호화에 사용된 데이터, IV(초기화 벡터) 및 키를 반환합니다.
// Arguments:
//   - key: 암호화 키를 생성할 바이트입니다.
//   - data: 암호화할 데이터입니다.
// Return:
//   - 암호화된 데이터, IV 및 암호화에 사용된 키입니다. (encryptedData, iv, aesKey, error)
func encryptData(key, data []byte) ([]byte, []byte, []byte, error) {
	// 입력 유효성 검사
	if len(key) < 32 {
		return nil, nil, nil, errors.New("key must be at least 32 bytes for AES-256")
	}
	if len(data) == 0 {
		return nil, nil, nil, errors.New("data cannot be empty")
	}

	// AES-256을 위해 키의 처음 32바이트를 사용
	aesKey := key[:32]

	// AES 암호화 블록 생성
	block, err := aes.NewCipher(aesKey)
	if err != nil {
		return nil, nil, nil, err
	}

	// 데이터 패딩 (PKCS#7)
	padding := block.BlockSize() - (len(data) % block.BlockSize())
	paddedData := make([]byte, len(data)+padding)
	copy(paddedData, data)
	for i := len(data); i < len(paddedData); i++ {
		paddedData[i] = byte(padding)
	}

	// IV 생성 (초기화 벡터)
	iv := make([]byte, block.BlockSize())
	if _, err := io.ReadFull(rand.Reader, iv); err != nil {
		return nil, nil, nil, err
	}

	// CBC 모드 암호화
	encryptedData := make([]byte, len(paddedData))
	mode := cipher.NewCBCEncrypter(block, iv)
	mode.CryptBlocks(encryptedData, paddedData)

	return encryptedData, iv, aesKey, nil
}