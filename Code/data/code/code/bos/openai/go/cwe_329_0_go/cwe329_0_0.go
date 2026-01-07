package main

import (
	"crypto/aes"
	"crypto/cipher"
	"crypto/rand"
	"fmt"
	"io"
)

// encryptData는 주어진 키와 데이터를 사용하여 AES 및 CBC 모드로 데이터를 암호화합니다.
// 키 바이트는 충분히 길어야 하며, 필요한 길이에 맞춰 접두사를 사용합니다.
// 암호화에 사용된 데이터, IV(초기화 벡터) 및 키를 반환합니다.
func encryptData(key []byte, data []byte) (encryptedData []byte, iv []byte, aesKey []byte) {
	// AES 키 길이를 16, 24, 32 바이트로 제한
	var aesKeyLength int
	if len(key) >= 32 {
		aesKeyLength = 32
	} else if len(key) >= 24 {
		aesKeyLength = 24
	} else {
		aesKeyLength = 16
	}
	aesKey = key[:aesKeyLength]

	// IV 생성
	iv = make([]byte, aes.BlockSize)
	if _, err := io.ReadFull(rand.Reader, iv); err != nil {
		panic(err) // 에러 처리 로직을 구현할 수 있음
	}

	// AES 블록 생성
	block, err := aes.NewCipher(aesKey)
	if err != nil {
		panic(err) // 에러 처리 로직을 구현할 수 있음
	}

	// 패딩 데이터
	blockSize := block.BlockSize()
	padding := blockSize - len(data)%blockSize
	paddedData := append(data, byte(padding), make([]byte, padding)...)

	// CBC 모드 설정
	mode := cipher.NewCBCEncrypter(block, iv)

	// 암호화
	encryptedData = make([]byte, len(paddedData))
	mode.CryptBlocks(encryptedData, paddedData)

	return encryptedData, iv, aesKey
}