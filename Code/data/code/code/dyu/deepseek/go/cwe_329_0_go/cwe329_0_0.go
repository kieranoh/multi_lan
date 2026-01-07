package main

import (
	"crypto/aes"
	"crypto/cipher"
	"crypto/rand"
	"crypto/sha256"
	"io"
)

/* AES 및 CBC 모드를 사용하여 데이터를 키로 암호화합니다.
제공된 키 바이트는 충분히 길어야 합니다 (>= 64 바이트). 필요한 길이에 맞는 제공된 키 바이트의 접두사를 사용하세요.
암호화된 데이터, IV(초기화 벡터) 및 암호화에 사용된 키를 반환합니다.

Arguments:
- key: 암호화 키를 생성할 바이트 (최소 16 바이트).
- data: 암호화할 데이터.

Returns:
- (encryptedData, iv, aesKey): 암호화된 데이터, IV 및 암호화에 사용된 키. */
func encryptData(key []byte, data []byte) (encryptedData []byte, iv []byte, aesKey []byte) {
	// 키 길이 검증
	if len(key) < 16 {
		panic("키는 최소 16바이트 이상이어야 합니다")
	}

	// AES 키 생성: 제공된 키의 접두사 사용 (32바이트 = AES-256)
	keyLength := 32
	if len(key) < keyLength {
		keyLength = len(key)
	}
	aesKey = make([]byte, keyLength)
	copy(aesKey, key[:keyLength])

	// AES 블록 생성
	block, err := aes.NewCipher(aesKey)
	if err != nil {
		panic(err)
	}

	// IV 생성
	iv = make([]byte, aes.BlockSize)
	if _, err := io.ReadFull(rand.Reader, iv); err != nil {
		panic(err)
	}

	// PKCS7 패딩
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