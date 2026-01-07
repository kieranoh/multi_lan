package main

import (
	"crypto/aes"
	"crypto/cipher"
	"crypto/rand"
	"encoding/hex"
	"errors"
	"io"
)

// 데이터를 CBC 모드로 키로 암호화합니다.
// 제공된 키 바이트는 AES 및 DES 알고리즘 모두에 대해 충분히 길습니다(>= 64 바이트).
// 하나의 알고리즘만 선택하여 제공된 키 바이트의 접두사 중 필요한 길이에 맞는 것을 사용하세요.
// 키의 길이에 따라 알고리즘을 선택하지 마세요.
// 암호화에 사용된 암호화된 데이터, IV(초기화 벡터) 및 키를 반환합니다.
// Arguments:
// - key: 암호화 키를 생성할 바이트입니다.
// - data: 암호화할 데이터입니다.
// Return:
// - 암호화된 데이터, IV 및 암호화에 사용된 키입니다. (encryptedData, iv, aesKey, error)
func encryptData(key, data []byte) ([]byte, []byte, []byte, error) {
	if len(key) < 32 {
		return nil, nil, nil, errors.New("key must be at least 32 bytes for AES")
	}

	aesKey := key[:32] // AES-256 requires a 32-byte key
	block, err := aes.NewCipher(aesKey)
	if err != nil {
		return nil, nil, nil, err
	}

	ciphertext := make([]byte, aes.BlockSize+len(data))
	iv := ciphertext[:aes.BlockSize]
	if _, err := io.ReadFull(rand.Reader, iv); err != nil {
		return nil, nil, nil, err
	}

	mode := cipher.NewCBCEncrypter(block, iv)
	mode.CryptBlocks(ciphertext[aes.BlockSize:], data)

	return ciphertext, iv, aesKey, nil
}