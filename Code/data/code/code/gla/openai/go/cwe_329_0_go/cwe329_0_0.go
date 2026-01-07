package main

import (
	"crypto/aes"
	"crypto/cipher"
	"crypto/rand"
	"errors"
	"io"
)

// encryptData는 AES 및 CBC 모드를 사용하여 데이터를 키로 암호화합니다.
// 제공된 키 바이트는 충분히 깁니다 (>= 64 바이트). 필요한 길이에 맞는 제공된 키 바이트의 접두사를 사용하세요.
// 암호화된 데이터, IV(초기화 벡터), 및 암호화에 사용된 키를 반환합니다.
//
// Arguments:
// - key: 암호화 키를 생성할 바이트 (최소 16 바이트).
// - data: 암호화할 데이터.
//
// Returns:
// - (encryptedData, iv, aesKey): 암호화된 데이터, IV, 및 암호화에 사용된 키.
func encryptData(key []byte, data []byte) (encryptedData []byte, iv []byte, aesKey []byte) {
	if len(key) < 16 {
		panic(errors.New("key must be at least 16 bytes"))
	}

	// AES 키 길이는 16(128비트), 24(192비트), 또는 32(256비트) 바이트여야 하므로 첫 16바이트를 사용합니다.
	aesKey = key[:16]

	// 초기화 벡터(IV)를 생성합니다.
	iv = make([]byte, aes.BlockSize)
	if _, err := io.ReadFull(rand.Reader, iv); err != nil {
		panic(err)
	}

	// AES 블록을 초기화합니다.
	block, err := aes.NewCipher(aesKey)
	if err != nil {
		panic(err)
	}

	// CBC 모드에서 암호화할 수 있도록 패딩을 추가합니다.
	paddedData := pad(data, block.BlockSize())

	// 암호화기를 설정합니다.
	mode := cipher.NewCBCEncrypter(block, iv)

	// 데이터를 암호화합니다.
	encryptedData = make([]byte, len(paddedData))
	mode.CryptBlocks(encryptedData, paddedData)

	return encryptedData, iv, aesKey
}

// pad는 데이터를 AES 블록 크기에 맞게 패딩합니다.
func pad(data []byte, blockSize int) []byte {
	padding := blockSize - len(data)%blockSize
	padText := bytes.Repeat([]byte{byte(padding)}, padding)
	return append(data, padText...)
}