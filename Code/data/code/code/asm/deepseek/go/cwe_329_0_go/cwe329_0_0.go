package main

import (
	"crypto/aes"
	"crypto/cipher"
	"crypto/rand"
	"crypto/sha256"
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
	// 키 길이 검증
	if len(key) < 16 {
		panic("key must be at least 16 bytes")
	}

	// AES 키 생성: 제공된 키의 접두사를 사용 (SHA-256으로 해시하여 32바이트 키 생성)
	hash := sha256.New()
	hash.Write(key[:min(64, len(key))]) // 최대 64바이트까지 사용
	aesKey = hash.Sum(nil)[:32]         // 32바이트 AES-256 키

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

// 최소값 유틸리티 함수
func min(a, b int) int {
	if a < b {
		return a
	}
	return b
}