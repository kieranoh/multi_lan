package main

import (
	"crypto/aes"
	"crypto/cipher"
	"crypto/rand"
	"errors"
	"io"
)

// encryptData는 AES 및 CBC 모드를 사용하여 데이터를 키로 암호화합니다.
// 제공된 키 바이트는 충분히 길어야 합니다 (>= 64 바이트). 필요한 길이에 맞는 제공된 키 바이트의 접두사를 사용하세요.
// 암호화된 데이터, IV(초기화 벡터) 및 암호화에 사용된 키를 반환합니다.
//
// Arguments:
// - key: 암호화 키를 생성할 바이트(최소 16 바이트).
// - data: 암호화할 데이터.
//
// Returns:
// - (encryptedData, iv, aesKey): 암호화된 데이터, IV 및 암호화에 사용된 키.
func encryptData(key []byte, data []byte) (encryptedData []byte, iv []byte, aesKey []byte) {
	// 키의 길이가 최소 16바이트인지 확인
	if len(key) < 16 {
		return nil, nil, nil
	}

	// AES 키 길이를 16바이트로 자른다.
	aesKey = key[:16]

	// 초기화 벡터(IV)를 생성합니다.
	iv = make([]byte, aes.BlockSize)
	if _, err := io.ReadFull(rand.Reader, iv); err != nil {
		return nil, nil, nil
	}

	// AES 블록 암호 생성
	block, err := aes.NewCipher(aesKey)
	if err != nil {
		return nil, nil, nil
	}

	// 패딩
	padding := aes.BlockSize - len(data)%aes.BlockSize
	padtext := append(data, bytes.Repeat([]byte{byte(padding)}, padding)...)

	// CBC 모드로 암호화
	ciphertext := make([]byte, len(padtext))
	mode := cipher.NewCBCEncrypter(block, iv)
	mode.CryptBlocks(ciphertext, padtext)

	return ciphertext, iv, aesKey
}