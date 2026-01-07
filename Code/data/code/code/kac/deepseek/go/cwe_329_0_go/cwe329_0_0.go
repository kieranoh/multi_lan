package main

import (
	"crypto/aes"
	"crypto/cipher"
	"crypto/rand"
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
	// AES 키 길이 결정 (16, 24, 또는 32 바이트)
	keyLength := 32 // 기본적으로 256비트 키 사용
	if len(key) < 16 {
		// 최소 길이 요구사항을 충족하지 않으면 빈 결과 반환
		return nil, nil, nil
	}

	// 가능한 키 길이 중 선택 (16, 24, 32)
	if len(key) >= 32 {
		keyLength = 32
	} else if len(key) >= 24 {
		keyLength = 24
	} else {
		keyLength = 16
	}

	// 키 접두사 사용
	aesKey = make([]byte, keyLength)
	copy(aesKey, key[:keyLength])

	// AES 블록 생성
	block, err := aes.NewCipher(aesKey)
	if err != nil {
		return nil, nil, nil
	}

	// IV 생성 (초기화 벡터)
	iv = make([]byte, aes.BlockSize)
	if _, err := io.ReadFull(rand.Reader, iv); err != nil {
		return nil, nil, nil
	}

	// PKCS7 패딩 적용
	padding := aes.BlockSize - len(data)%aes.BlockSize
	paddedData := make([]byte, len(data)+padding)
	copy(paddedData, data)
	for i := len(data); i < len(paddedData); i++ {
		paddedData[i] = byte(padding)
	}

	// CBC 모드 암호화
	encryptedData = make([]byte, len(paddedData))
	mode := cipher.NewCBCEncrypter(block, iv)
	mode.CryptBlocks(encryptedData, paddedData)

	return encryptedData, iv, aesKey
}