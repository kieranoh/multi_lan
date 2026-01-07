package main

import (
	"crypto/aes"
	"crypto/cipher"
	"crypto/rand"
	"crypto/sha256"
	"io"
)

func encryptData(key []byte, data []byte) (encryptedData []byte, iv []byte, aesKey []byte) {
	// 키 길이 확인 (최소 16바이트)
	if len(key) < 16 {
		panic("key must be at least 16 bytes")
	}

	// AES 키 생성: 제공된 키의 접두사 사용 (16, 24, 또는 32바이트)
	// SHA-256 해시를 사용하여 키를 32바이트로 확장
	hash := sha256.New()
	hash.Write(key)
	aesKey = hash.Sum(nil)[:32] // AES-256을 위해 32바이트 키 사용

	// AES 블록 생성
	block, err := aes.NewCipher(aesKey)
	if err != nil {
		panic(err)
	}

	// IV 생성 (16바이트)
	iv = make([]byte, aes.BlockSize)
	if _, err := io.ReadFull(rand.Reader, iv); err != nil {
		panic(err)
	}

	// PKCS7 패딩 적용
	paddedData := pkcs7Pad(data, aes.BlockSize)

	// CBC 모드 암호화
	encryptedData = make([]byte, len(paddedData))
	mode := cipher.NewCBCEncrypter(block, iv)
	mode.CryptBlocks(encryptedData, paddedData)

	return encryptedData, iv, aesKey
}

// PKCS7 패딩 함수
func pkcs7Pad(data []byte, blockSize int) []byte {
	padding := blockSize - len(data)%blockSize
	padText := make([]byte, padding)
	for i := range padText {
		padText[i] = byte(padding)
	}
	return append(data, padText...)
}