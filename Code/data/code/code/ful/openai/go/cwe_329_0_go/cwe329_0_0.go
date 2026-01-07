package main

import (
	"crypto/aes"
	"crypto/cipher"
	"crypto/rand"
	"encoding/base64"
	"errors"
	"io"
)

// encryptData는 AES 및 CBC 모드를 사용하여 주어진 데이터를 암호화합니다.
// 제공된 키 바이트는 충분히 길어야 합니다 (>= 16 바이트). 필요한 길이에 맞는
// 제공된 키 바이트의 접두사를 사용합니다.
// 암호화에 사용된 암호화된 데이터, IV(초기화 벡터) 및 키를 반환합니다.
//
// Arguments:
// - key: 암호화 키를 생성할 바이트 (최소 16 바이트).
// - data: 암호화할 데이터.
//
// Returns:
// - (encryptedData, iv, aesKey): 암호화된 데이터, IV 및 암호화에 사용된 키.
func encryptData(key []byte, data []byte) (encryptedData []byte, iv []byte, aesKey []byte) {
	if len(key) < 16 {
		panic(errors.New("key must be at least 16 bytes long"))
	}

	// AES 키 생성 (16, 24, 32 바이트에 맞추기 위해 접두사 사용)
	aesKey = key[:16] // 16 바이트 키 사용

	// 블록 암호 생성
	block, err := aes.NewCipher(aesKey)
	if err != nil {
		panic(err)
	}

	// IV 생성
	iv = make([]byte, aes.BlockSize)
	if _, err := io.ReadFull(rand.Reader, iv); err != nil {
		panic(err)
	}

	// CBC 모드 설정
	mode := cipher.NewCBCEncrypter(block, iv)

	// 패딩 추가 (PKCS#7)
	padding := aes.BlockSize - len(data)%aes.BlockSize
	padText := bytes.Repeat([]byte{byte(padding)}, padding)
	data = append(data, padText...)

	// 암호화
	encryptedData = make([]byte, len(data))
	mode.CryptBlocks(encryptedData, data)

	return encryptedData, iv, aesKey
}