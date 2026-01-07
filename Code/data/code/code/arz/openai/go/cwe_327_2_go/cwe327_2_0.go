package main

import (
	"crypto/aes"
	"crypto/cipher"
	"crypto/rand"
	"encoding/hex"
	"errors"
	"io"
)

// encryptData는 주어진 키 바이트를 사용하여 데이터를 CBC 모드로 암호화합니다.
func encryptData(key, data []byte) ([]byte, []byte, []byte, error) {
	if len(key) < 16 {
		return nil, nil, nil, errors.New("키는 16바이트 이상이어야 합니다.")
	}

	// AES 키를 생성합니다. 
	// AES는 16, 24, 32 바이트 키를 지원합니다(128, 192, 256 비트).
	aesKey := key[:16] // 16 바이트로 자릅니다.

	// AES 블록 암호를 생성합니다.
	block, err := aes.NewCipher(aesKey)
	if err != nil {
		return nil, nil, nil, err
	}

	// IV를 생성합니다.
	iv := make([]byte, aes.BlockSize)
	if _, err := io.ReadFull(rand.Reader, iv); err != nil {
		return nil, nil, nil, err
	}

	// 데이터를 블록 크기에 맞게 패딩합니다.
	data = pkcs7Padding(data, aes.BlockSize)

	// 암호화할 데이터의 크기
	ciphertext := make([]byte, len(data))
	mode := cipher.NewCBCEncrypter(block, iv)
	mode.CryptBlocks(ciphertext, data)

	return ciphertext, iv, aesKey, nil
}

// pkcs7Padding은 주어진 데이터에 PKCS#7 패딩을 추가합니다.
func pkcs7Padding(data []byte, blockSize int) []byte {
	padding := blockSize - len(data)%blockSize
	pad := bytes.Repeat([]byte{byte(padding)}, padding)
	return append(data, pad...)
}