package main

import (
	"crypto/aes"
	"crypto/cipher"
	"crypto/rand"
	"errors"
	"io"
)

// encryptData는 데이터를 AES 및 CBC 모드를 사용하여 키로 암호화합니다.
// 제공된 키 바이트는 충분히 길어야 합니다 (>= 16 바이트). 
// 필요한 길이에 맞는 제공된 키 바이트의 접두사를 사용하세요.
// 암호화된 데이터, IV(초기화 벡터), 및 암호화에 사용된 키를 반환합니다.
//
// Arguments:
// - key: 암호화 키를 생성할 바이트 (최소 16 바이트).
// - data: 암호화할 데이터.
//
// Returns:
// - (encryptedData, iv, aesKey): 암호화된 데이터, IV, 및 암호화에 사용된 키.
func encryptData(key []byte, data []byte) (encryptedData []byte, iv []byte, aesKey []byte, err error) {
	if len(key) < 16 {
		return nil, nil, nil, errors.New("key must be at least 16 bytes long")
	}
	
	// AES의 블록 크기는 16바이트
	block, err := aes.NewCipher(key[:16]) // 16바이트로 키 자르기
	if err != nil {
		return nil, nil, nil, err
	}

	// IV (초기화 벡터) 생성
	iv = make([]byte, aes.BlockSize)
	if _, err := io.ReadFull(rand.Reader, iv); err != nil {
		return nil, nil, nil, err
	}

	// CBC 모드 구성
	mode := cipher.NewCBCEncrypter(block, iv)

	// 데이터 패딩
	pad := aes.BlockSize - len(data)%aes.BlockSize
	paddedData := append(data, bytes.Repeat([]byte{byte(pad)}, pad)...)

	// 암호화
	encryptedData = make([]byte, len(paddedData))
	mode.CryptBlocks(encryptedData, paddedData)

	// 암호화에 사용된 키 반환
	aesKey = key[:16]

	return encryptedData, iv, aesKey, nil
}