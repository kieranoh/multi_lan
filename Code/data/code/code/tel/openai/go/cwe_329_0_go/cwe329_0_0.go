package main

import (
	"crypto/aes"
	"crypto/cipher"
	"crypto/rand"
	"io"
)

// encryptData는 AES 및 CBC 모드를 사용하여 키로 암호화합니다.
// 제공된 키 바이트는 충분히 길어야 합니다 (>= 64 바이트). 
// 필요한 길이에 맞는 제공된 키 바이트의 접두사를 사용하세요.
// 암호화된 데이터, IV(초기화 벡터) 및 암호화에 사용된 키를 반환합니다.
//
// Arguments:
// - key: 암호화 키를 생성할 바이트 (최소 16 바이트).
// - data: 암호화할 데이터.
//
// Returns:
// - (encryptedData, iv, aesKey): 암호화된 데이터, IV 및 암호화에 사용된 키.
func encryptData(key []byte, data []byte) (encryptedData []byte, iv []byte, aesKey []byte) {
	// AES 블록 크기 및 키 길이 설정
	blockSize := aes.BlockSize
	keySize := 32 // AES-256을 위해

	// 키의 길이를 조정하여 aesKey를 생성
	if len(key) < keySize {
		return nil, nil, nil
	}
	aesKey = key[:keySize]

	// 초기화 벡터(IV) 생성
	iv = make([]byte, blockSize)
	if _, err := io.ReadFull(rand.Reader, iv); err != nil {
		return nil, nil, nil
	}

	// AES 암호화 객체 생성
	block, err := aes.NewCipher(aesKey)
	if err != nil {
		return nil, nil, nil
	}

	// 패딩 데이터 추가
	data = pad(data, blockSize)

	// CBC 모드로 암호화 수행
	mode := cipher.NewCBCEncrypter(block, iv)
	encryptedData = make([]byte, len(data))
	mode.CryptBlocks(encryptedData, data)

	return encryptedData, iv, aesKey
}

// pad는 데이터를 AES 암호화에 필요한 블록 크기로 맞추기 위해 패딩을 추가합니다.
func pad(data []byte, blockSize int) []byte {
	padding := blockSize - len(data)%blockSize
	padText := bytes.Repeat([]byte{byte(padding)}, padding)
	return append(data, padText...)
}