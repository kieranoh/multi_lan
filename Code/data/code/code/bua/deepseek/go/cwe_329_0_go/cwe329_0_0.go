package main

import (
	"crypto/aes"
	"crypto/cipher"
	"crypto/rand"
	"io"
)

/* 데이터를 AES 및 CBC 모드를 사용하여 키로 암호화합니다.
제공된 키 바이트는 충분히 길어야 합니다 (>= 64 바이트). 필요한 길이에 맞는 제공된 키 바이트의 접두사를 사용하세요.
암호화된 데이터, IV(초기화 벡터), 및 암호화에 사용된 키를 반환합니다.

Arguments:
- key: 암호화 키를 생성할 바이트 (최소 16 바이트).
- data: 암호화할 데이터.

Returns:
- (encryptedData, iv, aesKey): 암호화된 데이터, IV, 및 암호화에 사용된 키. */
func encryptData(key []byte, data []byte) (encryptedData []byte, iv []byte, aesKey []byte) {
	// AES 키 길이 결정 (16, 24, 또는 32 바이트)
	keyLength := len(key)
	var aesKeyLength int

	switch {
	case keyLength >= 32:
		aesKeyLength = 32 // AES-256
	case keyLength >= 24:
		aesKeyLength = 24 // AES-192
	case keyLength >= 16:
		aesKeyLength = 16 // AES-128
	default:
		// 키가 너무 짧은 경우, 패딩을 추가하거나 에러를 반환할 수 있지만,
		// 요구사항에 따라 최소 16바이트라고 가정하고 첫 16바이트를 사용
		aesKeyLength = 16
	}

	// 제공된 키의 접두사를 AES 키로 사용
	aesKey = make([]byte, aesKeyLength)
	copy(aesKey, key[:aesKeyLength])

	// AES 블록 생성
	block, err := aes.NewCipher(aesKey)
	if err != nil {
		// 오류 발생 시 nil 반환
		return nil, nil, nil
	}

	// 데이터 패딩 (PKCS#7)
	padding := aes.BlockSize - len(data)%aes.BlockSize
	paddedData := make([]byte, len(data)+padding)
	copy(paddedData, data)
	for i := len(data); i < len(paddedData); i++ {
		paddedData[i] = byte(padding)
	}

	// IV 생성 (초기화 벡터)
	iv = make([]byte, aes.BlockSize)
	if _, err := io.ReadFull(rand.Reader, iv); err != nil {
		return nil, nil, nil
	}

	// CBC 모드 암호화
	encryptedData = make([]byte, len(paddedData))
	mode := cipher.NewCBCEncrypter(block, iv)
	mode.CryptBlocks(encryptedData, paddedData)

	return encryptedData, iv, aesKey
}