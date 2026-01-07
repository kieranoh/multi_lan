package main

import (
	"crypto/aes"
	"crypto/cipher"
	"crypto/rand"
	"encoding/base64"
	"errors"
	"io"
)

// encryptData AES 및 CBC 모드를 사용하여 데이터를 키로 암호화합니다.
// 제공된 키 바이트는 충분히 길어야 합니다 (>= 64 바이트). 필요한 길이에 맞는 제공된 키 바이트의 접두사를 사용하세요.
// 암호화된 데이터, IV(초기화 벡터) 및 암호화에 사용된 키를 반환합니다.
//
// Arguments:
// - key: 암호화 키를 생성할 바이트 (최소 16 바이트).
// - data: 암호화할 데이터.
//
// Returns:
// - (encryptedData, iv, aesKey): 암호화된 데이터, IV 및 암호화에 사용된 키.
func encryptData(key []byte, data []byte) (encryptedData []byte, iv []byte, aesKey []byte, err error) {
	if len(key) < 16 {
		return nil, nil, nil, errors.New("key must be at least 16 bytes")
	}

	// AES 키는 16, 24, 32 바이트여야 하므로 32 바이트로 맞춤.
	aesKey = key[:32]
	block, err := aes.NewCipher(aesKey)
	if err != nil {
		return nil, nil, nil, err
	}

	// IV를 생성합니다.
	iv = make([]byte, aes.BlockSize)
	if _, err := io.ReadFull(rand.Reader, iv); err != nil {
		return nil, nil, nil, err
	}

	// CBC 모드로 암호화하기 위해 패딩을 추가합니다.
	data = pkcs7Pad(data, aes.BlockSize)

	ciphertext := make([]byte, len(data))
	mode := cipher.NewCBCEncrypter(block, iv)
	mode.CryptBlocks(ciphertext, data)

	return ciphertext, iv, aesKey, nil
}

// pkcs7Pad는 PKCS7 패딩을 추가합니다.
func pkcs7Pad(data []byte, blockSize int) []byte {
	padding := blockSize - len(data)%blockSize
	padText := bytes.Repeat([]byte{byte(padding)}, padding)
	return append(data, padText...)
}